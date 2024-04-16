# ChatGPT_WebSever
在ChatGPT3.5的帮助下写的一个网页服务器，用于学习和个人网站的建设。

# 处理多个客户端连接请求方式
多线程，线程池

# 设计思路
- Server类负责服务器的启动、关闭和添加处理程序等功能。
- Router类负责解析请求和路由功能，即根据请求的路径选择合适的处理程序（默认静态处理，登录注册等动态请求以.cgi为标识）。
- Request类，存储客户端发送的请求，包括请求方法、路径、请求体和请求头等信息。
- Response类，表示服务器返回的响应，包括状态码、响应头和响应体等信息。
- 定义Handler接口，所有处理程序都需要继承它并实现handle(Request, Response)函数。
- StaticHandler类，继承自Handler类，用于处理静态资源请求，即返回服务器上的文件。

# TODO
- epoll
- 用单例模式实现配置文件功能



