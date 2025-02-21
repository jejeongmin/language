const int getArraySizeFail()
{
	return 32;
}

constexpr int getArraySize()
{
	return 32;
}

int main1()
{
	int myArray[getArraySize()];	// OK
	//int myArray2[getArraySizeFail()];	// fail
	myArray[0] = 1;
	return 0;
}
