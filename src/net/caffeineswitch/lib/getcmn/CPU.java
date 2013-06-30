package net.caffeineswitch.lib.getcmn;

public class CPU {
	static{
		if("x86".equals(System.getProperty("os.arch"))){
			System.loadLibrary("CPUUsage");
		}else if("amd64".equals(System.getProperty("os.arch"))){
			System.loadLibrary("CPUUsage_64");
		}
	}

	public native double getCPUUsage();

	public CPU() {
	}
}
