using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.ComponentModel;

// http://www.atmarkit.co.jp/fdotnet/csharp_abc/csharp_abc_017/csharp_abc01.html
namespace DelegateSample
{
    delegate int Sample(int x, int y);
    class Class2
    {
        public int methodMult(int x, int y)
        {
            return x * y;
        }
        public int methodPlus(int x, int y)
        {
            return x + y;
        }
    }
    class Class1
    {
        public static void calc(int x, int y, Sample calcMethod)
        {
            int result = calcMethod(x, y);
            Console.WriteLine(result);
        }
        public static void Test(string[] args)
        {
            Class2 instance = new Class2();
            calc(2, 3, new Sample(instance.methodMult));
            calc(2, 3, new Sample(instance.methodPlus));
        }
    }
}

// http://www.atmarkit.co.jp/fdotnet/csharp_abc/csharp_abc_013/csharp_abc03.html
namespace EventSample
{
    public delegate void SampleEventHandler(object sender, EventArgs e);
    class Class1
    {
        public static event SampleEventHandler sampleEvent
        {
            add
            {
                Console.WriteLine("add called");
            }
            remove
            {
                Console.WriteLine("remove called");
            }
        }
        public static void handler(object o, EventArgs e)
        {
            Console.WriteLine("handler called");
        }
        public static void Test(string[] args)
        {
            Console.WriteLine("add event handler");
            sampleEvent += new SampleEventHandler(handler);
            Console.WriteLine("remove event handler");
            sampleEvent -= new SampleEventHandler(handler);
            Console.WriteLine("done");
        }
    }
}
namespace EventSample2
{
    namespace systemLibrary
    {
        abstract class ClassBase
        {
            public abstract void onEvenet();
        }
        class ClassLibrary
        {
            public static void fireEvent(ClassBase instance)
            {
                instance.onEvenet();
            }
        }
    }

    namespace userProgram
    {
        class ClassDelived : systemLibrary.ClassBase
        {
            public override void onEvenet()
            {
                Console.WriteLine("onEvent called");
            }
        }
        class Class1
        {
            public static void Test(string[] args)
            {
                ClassDelived instance = new ClassDelived();
                systemLibrary.ClassLibrary.fireEvent(instance);
            }
        }
    }
}

// http://yohshiy.blog.fc2.com/blog-entry-263.html
namespace AnotherEventSample
{
    delegate void HelloDelegate(string name);

    class Button
    {
        // イベント
        // (クラス定義内でしか event は使えない)
        public event HelloDelegate SomeEvent = delegate(string name) { };

        // イベントの発生
        public void Clicked(string name)
        {
            Console.WriteLine("<Button Clicked>");
            // 登録した関数を呼び出す
            // (直接には Button クラス内でしか実行できない)
            SomeEvent(name);
        }
    }

    class Foo
    {
        public void Hello(string name)
        {
            Console.WriteLine("(method) : Hello {0}!", name);
        }
    }

    class Program
    {
        static void StaticHello(string name)
        {
            Console.WriteLine("(static) : Hello {0}!", name);
        }

        public static void Test(string[] args)
        {
            Foo foo = new Foo();

            Button btn = new Button();

            // 関数の登録(アタッチ)
            btn.SomeEvent += foo.Hello;
            btn.SomeEvent += StaticHello;
            btn.SomeEvent += (string name) =>
            {
                Console.WriteLine("(lambda) : Hello {0}!", name);
            };

            // イベントの発生
            btn.Clicked("world");
        }
    }
}

namespace EventTest {
    public class MyEventArgs : EventArgs
    {
        public MyEventArgs(int n, String s)
        {
            this.num = n;
            this.str = s;
        }

        public int num {get; set;}
        public String str { get; set; }
    }
    public class SubEventArgs : MyEventArgs
    {
        public SubEventArgs(int n, String s, double d) :
            base(n ,s)
        {
            ddd = d;
        }
        public double ddd { get; set;}
    }
    public delegate void EventHandler(object sender, MyEventArgs arg);

    public class SuperClass {
        public event EventHandler handler;
        public void fireEvent() {
            handler(this, createEventArgs());
        }
        protected virtual MyEventArgs createEventArgs()
        {
            return new MyEventArgs(1, "super");
        }
    }
    public class SubClass {

        protected virtual MyEventArgs createEventArgs()
        {
            return new SubEventArgs(2, "sub", 2.0);
        }
    }

    class MySubscriber
    {
        private void myHandler(object sender, MyEventArgs a)
        {
            Console.WriteLine("myHnadler" + a.str);
        }
        private void subHandler(object sender, SubEventArgs a)
        {
            Console.WriteLine("subHnadler" + a.str);
        }
        static public void Test()
        {
            MySubscriber subscriber = new MySubscriber();
            SuperClass superC = new SuperClass();
            SubClass subC = new SubClass();

            superC.handler += subscriber.myHandler;
            // superC.handler += subscriber.subHandler; NG
        }
    }
}

namespace Test {
    class Program
    {
        static void Main(string[] args)
        {
            DelegateSample.Class1.Test(args);
            EventSample.Class1.Test(args);
            EventSample2.userProgram.Class1.Test(args);

            AnotherEventSample.Program.Test(args);
        }
    }

}
