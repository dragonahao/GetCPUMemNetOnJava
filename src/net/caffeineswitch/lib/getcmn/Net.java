package net.caffeineswitch.lib.getcmn;

public class Net {
	static{
		if("x86".equals(System.getProperty("os.arch"))){
			System.loadLibrary("NetUsage");
		}else if("amd64".equals(System.getProperty("os.arch"))){
			System.loadLibrary("NetUsage_64");
		}
	}

	public native void initNetIntf();

	public native int getNetIntfNum();

	public native String getNetIntfDesc(int i);

	public native long getNetIntfInOctet(int i);

	public native long getNetIntfOutOctet(int i);

	public Net() {

	}
}
