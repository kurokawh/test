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
        public MyEventArgs() { }
        public virtual void parseJson(object o)
        {
            this.num = 1;
            this.str = "base!";
        }

        public int num {get; set;}
        public String str { get; set; }
    }
    public class SubEventArgs : MyEventArgs
    {
        public override void parseJson(object o)
        {
            base.parseJson(o);
            ddd = 2.22;
            str = "sub!";
        }
        public double ddd { get; set;}
    }

    public class SuperClass<T> 
        where T : MyEventArgs, new()
    {
        public delegate void EventHandler(object sender, T arg);

        public event EventHandler handler;
        public void fireEvent() {
            object json = this;
            handler(this, createEventArgs(json));
        }
        protected virtual T createEventArgs(object o)
        {
            T arg = new T();
            arg.parseJson(o);
            return arg;
        }
    }
    public class SubClass : SuperClass<SubEventArgs> 
    {

    }

    class MySubscriber
    {
        private void myHandler(object sender, MyEventArgs a)
        {
            Console.WriteLine("myHnadler: " + a.str);
        }
        private void subHandler(object sender, SubEventArgs a)
        {
            Console.WriteLine("subHnadler: " + a.str);
        }
        static public void Test()
        {
            MySubscriber subscriber = new MySubscriber();
            SuperClass<MyEventArgs> superC = new SuperClass<MyEventArgs>();
            superC.handler += subscriber.myHandler;
            superC.fireEvent();

            SubClass subC = new SubClass();
            subC.handler += subscriber.subHandler;
            subC.fireEvent();
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

            EventTest.MySubscriber.Test();
        }
    }

}
