class NotConst
{
public:
	void normalFunc() const {}
};
class ConstTest
{
public:
	void constFunc(int val) const
	{
		m_val = val;
		m_normal.normalFunc();
		return;
	}
private:
	/*mutable*/ int m_val;
	/*mutable*/ NotConst m_normal;
};
