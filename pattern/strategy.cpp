#include <iostream>
#include <map>

#define CUR_STRATEGY ((Strategy*)curStrategy())
#define DEC_STRATEGY(ClassName)  class ClassName; friend class ClassName

class Context
{
public:
	Context() : m_pNormalStrategy(NULL), m_pLowLatStrategy(NULL)
	{
	}

	~Context()
	{
		if(m_pNormalStrategy)
		{
			delete m_pNormalStrategy;
		}
		if(m_pLowLatStrategy)
		{
			delete m_pLowLatStrategy;
		}
	}

	class Strategy
	{
		public:
			void  setContext(Context* pContext)
			{
				m_pContext = pContext;
			}

			virtual ~Strategy()
			{
			}

		protected:
			Context* getContext()
			{
				return m_pContext;
			}

		private:
			Context* m_pContext;
	};

	void AddNormalStrategy(Strategy* strategy)
	{
		m_pNormalStrategy = strategy;
		strategy->setContext(this);
	}

	void AddLowLatStrategy(Strategy* strategy)
	{
		m_pLowLatStrategy = strategy;
		strategy->setContext(this);
	}

	void setStrategyType(int type)
	{
		m_fakeStrategy = type;
	}

protected:
	Strategy* curStrategy()
	{
		if (m_pNormalStrategy && m_fakeStrategy == 1)
		{
			return m_pNormalStrategy;
		}
		
		if (m_pLowLatStrategy && m_fakeStrategy == 2)
		{
			return m_pLowLatStrategy;
		}

		return NULL;
	}

	int m_fakeStrategy;
	Strategy *m_pNormalStrategy;
	Strategy *m_pLowLatStrategy;

	friend class Strategy;
};


class JitterBuffer : public Context
{
public:
		class Strategy : public Context::Strategy 
		{
			public:
				virtual void doJob() = 0;
		};

		void show()
		{
			CUR_STRATEGY->doJob();
		}

private:
		void innerShow()
		{
			std::cout<<"Hello, I'm JitterBuffer"<<std::endl;
		}

public:
	DEC_STRATEGY(NormalStrategy);
	DEC_STRATEGY(LowLatencyStrategy);
};

class JitterBuffer::NormalStrategy : public JitterBuffer::Strategy 
{
public:
	void doJob()
	{
		std::cout<<"Using Normal Strategy"<<std::endl;
		JitterBuffer* jitter = (JitterBuffer*)getContext();
		jitter->innerShow();
	}
};

class JitterBuffer::LowLatencyStrategy : public JitterBuffer::Strategy 
{
public:
	void doJob()
	{
		std::cout<<"Using LowLatency Strategy"<<std::endl;
		JitterBuffer* jitter = (JitterBuffer*)getContext();
		jitter->innerShow();
	}
};

int main()
{
	JitterBuffer jitter;
	jitter.AddNormalStrategy(new JitterBuffer::NormalStrategy());
	jitter.AddLowLatStrategy(new JitterBuffer::LowLatencyStrategy());

	jitter.setStrategyType(1);
	jitter.show();

	std::cout<<std::endl<<std::endl;

	jitter.setStrategyType(2);
	jitter.show();

	return 0;
}
