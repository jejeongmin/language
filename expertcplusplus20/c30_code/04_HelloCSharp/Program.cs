using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

/*
	dll 과 dll 을 import 하는 프로그램은 x86/x64 설정이 같아야 한다.
    C# 의 경우는 IDE 의 설정이 아닌, 프로젝트 설정에서 x86/x64 설정을 직접 해줘야 한다.
*/

namespace _04_HelloCSharp
{
    class Program
    {
        [DllImport("04_HelloCppDll.dll", CharSet = CharSet.Unicode)]
        public static extern int FunctionInDLL(String s);

        static void Main(string[] args)
        {
            Console.WriteLine("Written by C#.");
            int result = FunctionInDLL("Some string from C#.");
            Console.WriteLine("C++ returned the value " + result);
        }
    }
}
