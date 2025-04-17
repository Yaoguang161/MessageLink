
```
MessageLink
├─ CMakeLists.txt
├─ README.md
├─ include
│  ├─ Utils
│  │  ├─ Any.hpp
│  │  ├─ NonCopyable.hpp
│  │  └─ function_traits.hpp
│  └─ test
│     └─ MessageBus.hpp
├─ src
│  └─ main.cpp
└─ start.sh

```
运行chmod +x start.sh
然后./start.sh


✅ 注册者：
Topic = "Drive" + 函数签名 = 一个唯一 key。

✅ 发送者： SendReq<void, int>(50, "Drive") 会生成同样的 key，查找所有注册过的处理函数并执行它们。