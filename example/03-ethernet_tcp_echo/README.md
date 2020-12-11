# 03-ethernet_tcp_echo

## 测试工具
    网线, 路由器(带dhcp)

## 测试软件
    串口助手

## 测试内容
    在main.c中设置需要连接的测试服务器地址和端口
    串口助手启动tcp, 端口和main.c设置的一致
    插上网线后, 程序会从dhcp获取地址, 前面板led变成常亮表示网络连接成功, 程序会一直尝试连接服务器, 连接成功后进行接收消息, 打印消息, 返回原消息
    串口助手tcp发送数据会接受到一样的数据返回