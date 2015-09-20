
//(1) there is no error for compiling JNIDemo.java first and then native.c
//(2) you should run command before run this program:
//"export LD_LIBRARY_PATH:."
//use this env to find the c library. after it, you needn't to set it again enen work dir changed.

public class JNIDemo {
		//public native static void hello();
		//place library at first
		static { // place library at static code block(static code will run only first before constructing a class)
			//1. load 
			System.loadLibrary("native"); //libnative.so for Linux. method hello() is from native.c.
		}
		public native int[] hello(int [] a); //int [] is array type.
		//public native int hello(String str, int[] a);
		public static void main(String args[]) {

			JNIDemo d = new JNIDemo();
			int [] a = {1, 2, 3};
			int [] b = null;
			int i;

			b = d.hello(a);
			for(i = 0; i < b.length; i++)
				System.out.println(b[i]);
			//2. java <--> c
			
			//3. call
			//hello() //for asserting hello with static
			//System.out.println(d.hello(a));
		}
		
}






