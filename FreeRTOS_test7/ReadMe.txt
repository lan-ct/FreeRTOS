信号量

二值信号量

通过xSemaphoreCreateBinary创建，返回的·是·这个信号量的指针SemaphoreHandle_t,在创建之后并不是立即可用，其初始计数为0，需要先使用xSemaphoreGive给予它初始量为1，之后才能
被获取。获取方式为vSemaphore,第二个·参数为等待的click数，若超过这个数依然没有获取，它会返回pdFalse或者0表示获取失败，当click设置为portMaxDelay时该函数会一直阻塞到获取到该信号量。释放
该信号量的方式为xSemaphoreGive.

计数信号量

通过xSemaphoreCreateCount创建，第一个参数为最大计数，第二个为初始计数，返回值依然是SemaphoreHandle_t,操作方式和二值信号量几乎一样


