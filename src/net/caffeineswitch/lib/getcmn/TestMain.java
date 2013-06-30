package net.caffeineswitch.lib.getcmn;

public class TestMain {
	public static void main(String[] args) {
		System.out.println(System.getProperty("os.arch"));
		Net net = new Net();
		net.initNetIntf();
		int i = net.getNetIntfNum();
		for(int j=1;j<=i;j++){
			System.out.println(j);
			System.out.println(net.getNetIntfDesc(j));
			System.out.println(net.getNetIntfOutOctet(j));
		}
		long preIn = net.getNetIntfInOctet(12);
		long preOut = net.getNetIntfOutOctet(12);

		CPU cpu = new CPU();
		Mem mem = new Mem();
		while(true){
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			System.out.println("CPU使用率(%):"+cpu.getCPUUsage());
			System.out.println("メモリ使用量(MByte):"+(mem.getUsedMem()/1024L/1024L));
			System.out.println("メモリ空き量(MByte):"+(mem.getFreeMem()/1024L/1024L));
			System.out.println("ネットワーク-In:(Kbps)"+((net.getNetIntfInOctet(12)-preIn)*8/1024L));
			System.out.println("ネットワーク-Out:(Kbps)"+((net.getNetIntfOutOctet(12)-preOut)*8/1024L));
			preIn = net.getNetIntfInOctet(12);
			preOut = net.getNetIntfOutOctet(12);
		}
	}

}
