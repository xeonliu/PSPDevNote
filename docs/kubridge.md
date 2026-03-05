# kubridge API

kubridge 是早期 CFW 为用户态程序提供的接口之一，绝大多数 CFW，如PRO, ARK 都支持它。

在 CFW 中有一个常驻内存的PRX模块SystemControl，导出了包括KUBridge在内的API。

如前所述，我们用户态应用的开发者要链接.S编译得到的存根库来使用这些函数。

kubridge被构建为静态存根库libpspkubridge.a，包含19个函数对象文件，可以被其他程序链接使用。

PSPDEV中已包含对应的存根库。

参见 pspdev/kubridge, ARK-4