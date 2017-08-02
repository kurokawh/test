using System;
using System.Collections.Generic;


namespace EventTest {
    public class MyEventArgs : EventArgs
    {
        public MyEventArgs() { }
        public virtual void setParams(object o)
        {
            this.num = 1;
            this.str = "base!";
        }

        public int num {get; set;}
        public String str { get; set; }
    }
    public class SubEventArgs : MyEventArgs
    {
        public override void setParams(object o)
        {
            base.setParams(o);
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
            arg.setParams(o);
            return arg;
        }
    }
    public class SubClass : SuperClass<SubEventArgs> 
    {

    }

    class TestSubscriber
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
            TestSubscriber subscriber = new TestSubscriber();
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

            EventTest.TestSubscriber.Test();
        }
    }

}
