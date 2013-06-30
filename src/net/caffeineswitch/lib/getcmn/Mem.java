package net.caffeineswitch.lib.getcmn;

public class Mem {
	static{
		if("x86".equals(System.getProperty("os.arch"))){
			System.loadLibrary("MemUsage");
		}else if("amd64".equals(System.getProperty("os.arch"))){
			System.loadLibrary("MemUsage_64");
		}
	}

	public native long getTotalMem();

	public native long getFreeMem();

	public native long getUsedMem();

	public Mem() {
	}
}
