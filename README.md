# threads_tutorial_c-11
C++11多线程入门教学

Lesson1:一个简单的例子

Lesson2:  

	2_1:创建线程、不同的传参方式、异常环境处理
	
	2_2:标识线程、转移线程所有权、最大硬件线程数量
	
Lesson3: 数据竞争 
	3_1.定义mutex对象为全局变量
	3_2.将mutex和受保护对象组织为一个类
Lesson4:死锁问题的产生和避免死锁的一般方法
Lesson5:用std::unique_lock灵活锁定和延迟初始化
Lesson6:用条件变量等待条件, 般用于：当一个线程必须等待其他线程完成之后才能执行时，避免“定期检查”所引起的资源和时间的浪费。
Lesson7:使用future等待一次性事件
	7_1.将子线程中的变量传入主线程
	7_2.将主线程中的变量传入单个子线程
	7_3.将主线程中的变量传入多个子线程
Lesson8:八种创建子线程的方法的总结
Lesson9:利用packaged_task类模板将任务与future相关联。
Lesson10:实现有时间限制的等待。
来自：https://zhuanlan.zhihu.com/c_149601753
