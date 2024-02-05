class ExampleOne{
	public static void main(String args[]){
		int $num = 1;
		char $hex = 0x4_5; //ignore underscore in any integer literal
		if('\141' == '\u0061')System.out.println("both represent the alphabet 'a' in ocatal and hexadecimal represtation of character: "+ '\u0061');
		for(int x = 0; x<3 ; x++){
			int y = -1;
			System.out.println("It is possible to define variable iteratively in java because it looses it life time when living any block of scope: so y is " + y);
		}
		if(true)System.out.println("worked");// don't use integer or 1  to indicate true or 0 for false it result error.
		System.out.println(0x2.2P2+" is equvalent with formula: (2*16^0 + 2*16^-1)*2^2");
		System.out.println(0x12.5P3+" is equvalent with formula: (1*16^1 + 2*16^0 + 5*16^-1)*2^3");
		System.out.println("Welcome back legend"+$num+"!char: "+$hex+" done! and default of floating point expression is double");
	int i =220;
	int e = 0xff;
	byte f =(byte) 0xf1;
	int g = f;
	int b;
	b = (byte) i;
	System.out.println("It is out of size of byte and integer value 220 is equvalent to: "+b+" let's see the result and e: "+e+"and f and g"+f+" "+g);
	}
}
