/*
*********************************************************************
* Copyright	(C), 2012-2013, CS&S. Co., Ltd.
* filename:	StateOS.h
* filepath:	f:\draven\中控板\zk_dravenv100\stateos
* --------------------------------------------------------
* History:
* <author>	@ Draven
* <time>    2017/07/20
* <version> V-0.0.1
* <desc>	-build this moudle
*********************************************************************
*/
#ifndef _STATEOS_H
#define _STATEOS_H

#define MAXTASKS 2U
volatile static unsigned char timers[MAXTASKS];

/***************************************************************/
/* 任务开始 */
#define _SS	                                            \
	static unsigned char _lc = 0U;                      \
	switch (_lc)                                        \
{                                                       \
	case 0U:
/***************************************************************/
/* 任务结束 */
#define _EE	                                            \
	break;                                              \
	default:                                            \
	break;                                              \
}										                \
	_lc = 0U;                                           \
	return 255U;
/***************************************************************/
/* 任务挂起等待 */
#define WaitX(tickets)                                  \
	_lc = (unsigned char)(__LINE__) % 255U + 1U;		\
if (_lc)                                                \
{                                                       \
	return (tickets);                                   \
}                                                       \
	break;                                              \
case ((unsigned char)(__LINE__) % 255U) + 1U:
/***************************************************************/
/* 运行任务 */
#define RunTask(TaskName,TaskID)	                    \
do{                                                     \
	if (timers[(TaskID)] == 0U)                         \
	{                                                   \
		timers[(TaskID)] = (TaskName)();                \
	}                                                   \
} while (0)
/***************************************************************/
/* 优先运行任务 内部不可 WaitX*/
#define RunTaskA(TaskName,TaskID)	                    \
{                                                       \
	if (timers[(TaskID)] == 0U)                         \
	{                                                   \
		timers[(TaskID)] = (TaskName)();                \
		continue;                                       \
	}                                                   \
}    /*前面的任务优先保证执行*/
/***************************************************************/
/* 调用一个子函数 */
#define CallSub(SubTaskName)                            \
do {                                                    \
	unsigned char currdt;                               \
	_lc=(unsigned char)(__LINE__)%255U+1U;              \
	if(_lc)                                             \
	{                                                   \
		return 0U;                                      \
	}                                                   \
		break;                                          \
	case (unsigned char)(__LINE__)%255U+1U:             \
		currdt=(SubTaskName)();                         \
	if(currdt!=255U)                                    \
		{                                               \
			return currdt;                              \
		}                                               \
} while(0);
/***************************************************************/
/* 初始化任务，实际上是给 timers 清零 */
#define InitTasks()	                                    \
do {                                                    \
		unsigned char i;                                \
		for(i=MAXTASKS;i>0U ;i--)                       \
		{                                               \
			timers[i-1U]=0U;                            \
		}                                               \
} while(0)
/***************************************************************/
/* 心跳更新 */
#define UpdateTimers()	                                \
do {                                                    \
	unsigned char i;                                    \
	for (i = MAXTASKS; i > 0U; i--)                     \
	{                                                   \
		if (timers[i - 1U] != 0U)                       \
		{                                               \
			if (timers[i - 1U] != 255U)                 \
			{                                           \
				timers[i - 1U]--;                       \
			}                                           \
		}                                               \
	}                                                   \
} while (0)
/***************************************************************/
#define SEM				unsigned int 
/***************************************************************/
	/*初始化信号量*/
#define InitSem(sem)		(sem)=0;
/***************************************************************/
	/*等待信号量*/
#define WaitSem(sem)		do{ (sem)=1; WaitX(0); if ((sem)>0) return 1;} while(0);
/***************************************************************/
	/*等待信号量或定时器溢出， 定时器tickets 最大为0xFFFE*/
#define WaitSemX(sem,tickets)  do { (sem)=(tickets)+1; WaitX(0); if((sem)>1){ (sem)--;  return 1;} } while(0);
/***************************************************************/
	/*发送信号量*/
#define SendSem(sem)		do {(sem)=0;} while(0);





#endif
	/*
	*********************************************************************
	* -StateOS.h	<File end.>
	* -f:\draven\中控板\zk_dravenv100\stateos
	*********************************************************************
	*/

