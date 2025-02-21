#pragma once

class CDummy
{
public:
	CDummy(void);
	virtual ~CDummy(void);

	void	print();

private:
	int		_arg1;
	char	_buf[1024];
};