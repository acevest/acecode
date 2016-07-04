public class Test
{
    
    private static int     uid = 27182818;
    private static int    gender = 1;
    private static int    age = 25;
    private static int    height = 123;     // cm
    private static int    weight = 45;     // kg
    private static String  alias  = "Ace";
    private static int    type = 0;
    private static String BTAddress = "C8:0F:10:6A:B1:F0";
    private static String hexStr = "0123456789ABCDEF";

    private static UserInfo mUserInfo = new UserInfo(uid, gender, age, height, weight, alias, type);

    public static void main(String[] args){
        byte[] mBin = mUserInfo.getBytes(BTAddress);
        String mHex = BinaryToHexString(mBin);
        System.out.println(mHex);
    }
    
    public static String BinaryToHexString(byte[] bytes) {
        String result = "";
        String hex = "";
        for(int i=0; i<bytes.length; i++) {
            hex = String.valueOf(hexStr.charAt((bytes[i]&0xF0) >> 4));
            hex +=String.valueOf(hexStr.charAt((bytes[i]&0x0F)));
            result += hex;
        }

        return result;
    }
    
}
