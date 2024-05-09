priority test
高优先级执行完毕后才能轮到低优先级，相同优先级轮流执行（时间片轮转开启）
时间片轮转开启方法：修改这个宏，为1时开启，为0时关闭#define configUSE_TIME_SLICING