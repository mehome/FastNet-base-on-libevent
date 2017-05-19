#ifndef _FAST_UTIL_H__
#define _FAST_UTIL_H__
#include <event2/util.h>
#include <time.h>


namespace fastbase
{
	typedef ev_uint8_t uint8;
	typedef ev_int8_t  int8;

	typedef  ev_uint16_t uint16;
	typedef ev_int16_t int16;
	
	typedef ev_uint32_t uint32;
	typedef ev_int32_t int32;

	typedef ev_uint64_t uint64;
	typedef ev_int64_t int64;

	void sleep(uint32 milliseconds);
	//void Sleep(ev_uint32_t )

	int32 StrToInt32(const char *value);
	int64 StrToInt64(const char *value);


	uint64 GetLocalTimeStamp();

#define SAFE_DELETE(ptr) { if(ptr){ try{ delete ptr; }catch(...){ printf("CATCH: *** SAFE_DELETE() crash! *** at %s, %d", __FILE__, __LINE__);} }}

#define SAFE_ARRAY_DELETE(ptr) { if(ptr){ try{ delete []ptr; }catch(...){ printf("CATCH: *** SAFE_DELETE() crash! *** at %s, %d", __FILE__, __LINE__);} }}

#define  ASSERT(condition) assert(condition)


	//////////////////////////////////////////////////////////////////////
	// ��ʱ�࣬�ԡ��롱Ϊ��λ
	//////////////////////////////////////////////////////////////////////
	class CTimer
	{
	public:
		CTimer(int nIntervalSecs = 0) { m_nInterval = nIntervalSecs; m_tUpdateTime = 0; }		// =0 : ���������ʼ��
		// virtual ~CTimer() {}
		CTimer& operator = (const CTimer& rhs)
		{
			m_nInterval = rhs.m_nInterval;
			m_tUpdateTime = rhs.m_tUpdateTime;
			return *this;
		}

	public:
		// ����ʱ���ǩ
		void	Update(void)					{ m_tUpdateTime = time(NULL); }

		// ���ڶ�ʱ����������ʱ�ӡ�ÿ�δ���ʱΪtrue��
		bool	ToNextTime(void)					{ if (IsExpire()) return Update(), true; else return false; }

		// ��ʼ��ʱ��Ƭ��(��������
		void	SetInterval(int nSecs)				{ m_nInterval = nSecs; }

		// ��ʼ����ʱ��(ͬSetInterval)
		void	Startup(int nSecs)				{ m_nInterval = nSecs; Update(); }

		// ʱ���Ƿ񴥷�(ֻ����һ��)����Startup���ʹ�ã���ʵ��ֻ����һ�ε�ʱ�ӡ�
		bool	TimeOver(void);//{ if(IsActive() && IsExpire()) return Clear(),true; return false; }
		void	Clear(void)					{ m_tUpdateTime = m_nInterval = 0; }
		bool	IsActive(void)					{ return m_tUpdateTime != 0; }
		void	IncInterval(int nSecs, int nLimit)	{ m_nInterval = __min(m_nInterval + nSecs, nLimit); }
		void	DecInterval(int nSecs)				{ m_nInterval = __max(m_nInterval - nSecs, 0); }

		// ����Ƿ�ʱ
		bool	IsExpire(void)
		{
			time_t daa = time(NULL);
			return daa >= m_tUpdateTime + m_nInterval;
		}
		// ����Ƿ�ʱ��ָ��ʱ��Ƭ������ͬһʱ���ǩ�������ͬ��ʱ�¼���(��ʵ��һ��������ƶ��ʱ��)
		bool	IsExpire(int nSecs)				{ return time(NULL) >= m_tUpdateTime + nSecs; }
		//��鵱ǰʱ���Ƿ񳬹�����ָ��ʱ�俪ʼ��ָ��ʱ������
		bool    IsExpire(time_t Start, int Interval){ return time(NULL) >= Start + Interval; }

		// ���ڱ䳤�ĳ�ʱ�¼���
		bool	ToNextTime(int nSecs)				{ if (IsExpire(nSecs)) return Update(), true; else return false; }

		// ʱ�ӻ���ۣ�������ֵ���������ֵ������ͬToNextTime(...)
		bool	ToNextTick(int nSecs);
		//	void	AppendInterval	(int nSecs)			{ if(ToNextTime()) m_nInterval=nSecs; else m_nInterval+=nSecs; }	// ToNextTime(): ��֤������nSecs��

	public: // get
		time_t		GetRemain()							{ return m_tUpdateTime ? __min(__max(m_nInterval - (time(NULL) - (int)m_tUpdateTime), 0), m_nInterval) : 0; }
		time_t		GetPast()							{ return m_tUpdateTime ? __min(__max((time(NULL) - (int)m_tUpdateTime), 0), m_nInterval) : 0; }
		//int		GetRemainTime()							{ return m_tUpdateTime ? __min(__max(m_nInterval - (int32)(time(NULL) - (int)m_tUpdateTime), 0), m_nInterval) : 0; }
	protected:
		int		m_nInterval;
		time_t	m_tUpdateTime;
	};

	
	
}

#endif/*_FAST_UTIL_H__*/
