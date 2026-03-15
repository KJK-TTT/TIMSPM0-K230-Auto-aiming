
# 检测图片中的矩形，计算矩形中心，并通过 UART 发送中心偏差。
import time
import os
import gc
import sys
import math
from math import atan, sqrt, atan2

# K230外设模块
from media.sensor import *    # Sensor 类与常量
from media.display import *   # Display 控制
from media.media import *     # MediaManager
import cv_lite                # 底层CV库
from time import ticks_ms     # 精确毫秒计时
from machine import UART      # UART 串口接口
from machine import FPIOA     # 引脚复用映射器(IO)

# IO映射
fpioa = FPIOA()
fpioa.set_function(11, fpioa.UART2_TXD)  # IO11 -> UART2 TX
fpioa.set_function(12, fpioa.UART2_RXD)  # IO12 -> UART2 RX

# UART 初始化
uart = UART(UART.UART2, baudrate=115200, bits=UART.EIGHTBITS,
            parity=UART.PARITY_NONE, stop=UART.STOPBITS_ONE)

# 显示区域
DETECT_WIDTH = ALIGN_UP(800, 16) # 显示宽度(16的倍数)
DETECT_HEIGHT = 480              # 显示高度

# 存放四个角点的数组
lst = [[1, 2], [1, 2], [1, 2], [1, 2]]

# 全局 sensor
sensor = None

# 传入 cv_lite 的图像尺寸格式为 [height, width]
image_shape = [320, 480]  # 高，宽

# 可调参数 
canny_thresh1 = 50        # Canny 边缘检测低阈值
canny_thresh2 = 150       # Canny 边缘检测高阈值
approx_epsilon = 0.04     # 多边形拟合精度
area_min_ratio = 0.001    # 最小面积比例
max_angle_cos = 0.5       # 最大余弦值
gaussian_blur_size = 5    
length_threshold = 120    # 对边长度差允许多少像素
last = 0                  # 保留变量

# 工具与数学函数
def format_coord(coord):
    """
    把整数坐标格式化为固定长度4字符
    返回字符串
    """
    return f"{coord:+04d}"

def find_max(arr):
    """
    在 cv_lite 返回的矩形列表中选取面积最大的矩形。
    返回最大的那一项（max_blob），若 arr 为空返回 None。
    """
    max_size = 0
    max_blob = None
    for s in range(len(arr)):
        if len(arr[s]) >= 4:
            area = arr[s][2] * arr[s][3]
            if area > max_size:
                max_blob = arr[s]
                max_size = area
    return max_blob

def are_segments_parallel(theta1, theta2, tolerance=30):
    """
    判断两条线段方向是否近似平行
    - theta1, theta2: 角度
    - tolerance: 容差30°
    返回 True 或 False。
    """
    angle_difference = abs(theta1 - theta2)
    if angle_difference > 180:
        angle_difference = angle_difference - 180
    # 当角度差接近 0 或接近 180（反向）时视为平行
    return math.isclose(angle_difference, 0, abs_tol=tolerance) or math.isclose(angle_difference, 180, abs_tol=tolerance)

def are_segments_vertical(theta1, theta2, tolerance=30):
    """
    判断两条线段是否近似垂直。
    与平行函数类似处理角度周期性。
    """
    angle_difference = abs(theta1 - theta2)
    if angle_difference > 180:
        angle_difference = angle_difference - 180
    return math.isclose(angle_difference, 90, abs_tol=tolerance)

def find_intersection(x1, y1, x2, y2, x3, y3, x4, y4):
    """
    计算两条直线的交点。
    返回 (int(x), int(y)) 像素坐标。
    """
    def calculate_determinant(A, B):
        return A[0] * B[1] - A[1] * B[0]
    
    AB = (x2 - x1, y2 - y1)
    AC = (x3 - x1, y3 - y1)
    CD = (x4 - x3, y4 - y3)

    det = calculate_determinant(AB, CD)
    if det == 0:
        # 平行或共线
        return None

    # 计算 t（交点参数）
    t = calculate_determinant(AC, CD) / det
    intersection_x = x1 + t * AB[0]
    intersection_y = y1 + t * AB[1]

    return int(intersection_x), int(intersection_y)

# 相机/显示控制函数 
def camera_init():
    global sensor
    sensor = Sensor()
    sensor.reset()  # 复位相机到默认状态

    # 设置抓图分辨率
    sensor.set_framesize(width=480, height=320)
    # 设置像素格式RGB888
    sensor.set_pixformat(Sensor.RGB888)
    # 初始化显示器
    Display.init(Display.ST7701, width=DETECT_WIDTH, height=DETECT_HEIGHT, fps=100, to_ide=True)
    # 初始化媒体管理器
    MediaManager.init()
    # 启动相机数据流
    sensor.run()

# 在程序退出或异常时务必调用以释放资源。
def camera_deinit():
    global sensor
    sensor.stop()               
    Display.deinit()          
    os.exitpoint(os.EXITPOINT_ENABLE_SLEEP)  # 允许睡眠
    time.sleep_ms(100)
    MediaManager.deinit()       # 释放媒体管理器所占资源

# 主处理循环
def capture_picture():
    fps = time.clock()         # 帧率计时器
    S_THRESHOLD = 2000         # 面积阈值，过滤极小区域

    while True:
        fps.tick()             # 更新帧率计时
        rect_flag = 0          # 标志：是否检测到满足条件的矩形
        current_time = ticks_ms()

        try:
            os.exitpoint() 
            global sensor

            #  抓图 
            img = sensor.snapshot()
            img_np = img.to_numpy_ref() 

            # 调用低层快速实现
            rects = cv_lite.rgb888_find_rectangles_with_corners(
                image_shape, img_np,
                canny_thresh1, canny_thresh2,
                approx_epsilon,
                area_min_ratio,
                max_angle_cos,
                gaussian_blur_size
            )

            # 如果检测到矩形
            if rects:
                # 选取面积最大的矩形
                max_rects = find_max(rects)
                # defensive: 如果 find_max 返回 None，跳过
                if max_rects is None:
                    rect_flag = 0
                else:
                    # 按原有格式提取四个角点
                    c = [[1, 2], [1, 2], [1, 2], [1, 2]]
                    for i in range(4):
                        c[i][0] = max_rects[2*i + 4]
                        c[i][1] = max_rects[2*i + 5]

                    # 绘制检测到的矩形外廓
                    for s in range(1, 5):
                        if s == 4:
                            s = 0
                        img.draw_line(c[s-1][0], c[s-1][1], c[s][0], c[s][1],
                                      color=(255, 0, 0), thickness=3)
                        img.draw_circle(c[s-1][0], c[s-1][1],
                                        2, color=(0, 0, 255), fill=True, thickness=3)

                    # 计算四条边长度（对边成对比较）
                    # len1: 点0->点1
                    len1 = sqrt((c[0][0]-c[1][0])**2 + (c[0][1]-c[1][1])**2)
                    # len2: 点2->点3
                    len2 = sqrt((c[2][0]-c[3][0])**2 + (c[2][1]-c[3][1])**2)
                    # len3: 点0->点3
                    len3 = sqrt((c[0][0]-c[3][0])**2 + (c[0][1]-c[3][1])**2)
                    # len4: 点1->点2
                    len4 = sqrt((c[1][0]-c[2][0])**2 + (c[1][1]-c[2][1])**2)

                    # 矩形近似面积
                    S = max_rects[2] * max_rects[3]

                    # 对边差值（绝对值）
                    err1 = abs(len1 - len2)  # 第一对对边差
                    err2 = abs(len3 - len4)  # 第二对对边差

                    # 基本几何性筛选：
                    if (S > S_THRESHOLD and err1 < length_threshold and err2 < length_threshold and
                        len1 > 30 and len2 > 30 and len3 > 30 and len4 > 30):

                        # 计算四条边的方向角
                        theta1 = math.degrees(math.atan2(c[0][1] - c[1][1], c[0][0] - c[1][0]))
                        theta2 = math.degrees(math.atan2(c[2][1] - c[3][1], c[2][0] - c[3][0]))
                        theta3 = math.degrees(math.atan2(c[0][1] - c[3][1], c[0][0] - c[3][0]))
                        theta4 = math.degrees(math.atan2(c[1][1] - c[2][1], c[1][0] - c[2][0]))

                        # 检查是否满足“近似矩形”的方向关系
                        is_line1_line2_parallel = are_segments_parallel(theta1, theta2)
                        is_line3_line4_parallel = are_segments_parallel(theta3, theta4)
                        is_line1_line3_vertical = are_segments_vertical(theta1, theta3)

                        # 若两组对边分别近似平行且一组边近似垂直（角接近直角），认定为“标准矩形”
                        if is_line1_line3_vertical and is_line1_line2_parallel and is_line3_line4_parallel:
                            rect_flag = 1
                            # 保存四个角到全局 lst（后面计算交点使用）
                            for s in range(4):
                                lst[s][0] = c[s][0]
                                lst[s][1] = c[s][1]
                        else:
                            rect_flag = 0
                    else:
                        rect_flag = 0
            else:
                rect_flag = 0

            #  若识别出标准矩形 
            if rect_flag == 1:
                # 计算对角线交点（两条对角线：0-2 与 1-3）
                intersection = find_intersection(
                    lst[0][0], lst[0][1],
                    lst[2][0], lst[2][1],
                    lst[1][0], lst[1][1],
                    lst[3][0], lst[3][1]
                )

                # 如果交点为 None
                if intersection is None:
                    # 显示错误信息
                    img.draw_string_advanced(0, 0, 30, "intersection error", color=(255, 0, 0), scale=2)
                    Display.show_image(img, x=(800-480)//2, y=(480-320)//2)
                else:
                    # 绘制中心点（红色）
                    img.draw_circle(intersection[0], intersection[1], 1, color=(255, 0, 0), thickness=4)

                    # 在图像左上角显示中心坐标
                    img.draw_string_advanced(0, 0, 30, "(x=%s,y=%s)" % (intersection[0], intersection[1]),
                                             color=(255, 255, 0), scale=3)

                    # 用绿色绘制最终确认的矩形
                    for s in range(1, 5):
                        if s == 4:
                            s = 0
                        img.draw_line(c[s-1][0], c[s-1][1], c[s][0], c[s][1], color=(0, 255, 0), thickness=3)
                        img.draw_circle(c[s-1][0], c[s-1][1], 2, color=(0, 0, 255), fill=True, thickness=3)

                    # 计算偏差：把检测中心和图像中心（240,160）做差
                    # 注意：这里 240,160 是 sensor 的中心（width/2=480/2, height/2=320/2）
                    wucha_xcenter = 240 - intersection[0]
                    wucha_ycenter = 160 - intersection[1]

                    # 构造输出字符串
                    out_str1 = '['
                    out_str1 += f'{format_coord(wucha_xcenter)}'
                    out_str1 += f'{format_coord(wucha_ycenter)}'
                    out_str1 += '*]'

                    # 通过 UART 发送（下位机按协议解析）
                    uart.write(out_str1)

                    # 在图上绘制 FPS 信息（作为调试）
                    img.draw_string_advanced(200, 0, 30, "fps:%s" % int(fps.fps()), color=(0, 255, 0))

                    # 显示图像
                    Display.show_image(img, x=(800-480)//2, y=(480-320)//2)

            #  未检测到合格矩形 
            else:
                # 显示 FPS 与阈值，便于调试
                img.draw_string_advanced(20, 50, 30, "fps:%s" % int(fps.fps()), color=(0, 255, 0))
                img.draw_string_advanced(10, 0, 30, "S_THRESHOLD:{}".format(S_THRESHOLD), color=(255, 0, 0))

                # 显示图像
                Display.show_image(img, x=(800-480)//2, y=(480-320)//2)

                # 发送占位值给下位机，表示“未检测到目标”
                wucha_xcenter = 999
                wucha_ycenter = 999
                out_str1 = '['
                out_str1 += format_coord(wucha_xcenter)
                out_str1 += format_coord(wucha_ycenter)
                out_str1 += '*]'
                uart.write(out_str1)

        except KeyboardInterrupt as e:
            print("user stop: ", e)
            break

        except BaseException as e:
            print(f"Exception {e}")
            break


#  程序入口 
def main():
    # 允许通过 os.exitpoint 与底层交互
    os.exitpoint(os.EXITPOINT_ENABLE)
    camera_is_init = False
    try:
        print("camera init")
        camera_init()
        camera_is_init = True

        print("camera capture")
        capture_picture()

    except Exception as e:
        # 上层异常处理：打印错误并在 finally 中释放资源
        print(f"Exception {e}")

    finally:
        # 若摄像头已初始化，退出时反初始化以释放资源
        if camera_is_init:
            print("camera deinit")
            camera_deinit()

if __name__ == "__main__":
    main()
