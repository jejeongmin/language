unique_ptr �� �ܵ� �������� ǥ���ϱ� ������ ������ �� ����.
std::move �� �̿��� �̵��� �����ϴ�.

reset() �� �̿��ϸ�, unique_ptr ���� �����͸� �����ϰ�, �ʿ��ϴٸ� �̸� �ٸ� �����ͷ� �����Ҽ� �ִ�.
ex)
mysimplePtr.reset();
mysimplePtr.reset(new Simple());

release() �� �̿��ϸ�, unique_ptr �� ���� �������� ���踦 ���� �� �ִ�.
Simple* ptr = mysimplePtr.reset();
delete ptr;
ptr = nullptr;