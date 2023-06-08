# ChatGPT_WebSever
基于ChatGPT(gpt-3.5-turbo)写的一个简单WeServer，大致是问它如何设计类合理，手残没有保存原始对话。

使用了线程池实现并发处理客户端连接请求。后面有时间会逐渐完善这个项目。

# 头文件说明
server.h：定义了 Server 类，实现了服务器的启动、关闭和添加处理程序等功能。

router.h：定义了 Router 类，实现了路由功能，即根据请求的路径选择合适的处理程序。

handler.h：定义了 Handler 类，为处理程序的基类，所有处理程序都需要继承它并实现 handle() 函数。

request.h：定义了 Request 类，表示客户端发送的请求，包括请求方法、路径、请求体和请求头等信息。

response.h：定义了 Response 类，表示服务器返回的响应，包括状态码、响应头和响应体等信息。

static_handler.h：定义了 StaticHandler 类，继承自 Handler 类，用于处理静态资源请求，即返回服务器上的文件。

# 调用逻辑

