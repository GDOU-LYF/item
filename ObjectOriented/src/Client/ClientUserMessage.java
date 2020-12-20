package Client;

import Server.Server;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ClientUserMessage extends Thread {
    private final User user;
    private final DataInputStream dis;
    private final DataOutputStream dos;
    private String message;

    public ClientUserMessage(User user, DataInputStream dis, DataOutputStream dos) {
        this.user = user;
        this.dis = dis;
        this.dos = dos;
    }

    @Override
    public void run() {
        super.run();
        String regex = "\\[[^\\]]*\\]";//匹配中括号
        Pattern compile = Pattern.compile(regex);
        while (true) {
            try {
                Thread.sleep(50);
                synchronized (user) {
                    message = dis.readUTF();
                }
                System.out.println("(get)Client: "+message);
                if (!"".equals(message)) {
                    if (message.indexOf("get-chat[") == 0) {//接受到信息
                        // "get-chat["+chatMessage[0]+"],send=["+chatMessage[1]+"];"
                        Matcher matcher = compile.matcher(message);
                        ArrayList<String> arrayList = new ArrayList<>();
                        while (matcher.find()) {
                            arrayList.add(matcher.group().replaceAll("\\[|\\]", ""));
                        }
                        System.out.println("Client-" + user.getUID() + ":来自" + arrayList.get(0) + "客户端的消息:" + arrayList.get(1));
                    } else if ("sendMessage:(Yes)".equals(message)) {
                        System.out.println("Client-" + user.getUID() + ":sendMessage=" + message);
                    } else if (message.indexOf("get-wait[") == 0) {//等待命令
                        Matcher matcher = compile.matcher(message);//"get-wait[" + userUID[0] + "],command=[wait],send=[" + userUID[1] + "];";
                        StringBuilder merge = new StringBuilder();
                        while (matcher.find()) {
                            merge.append(matcher.group().replaceAll("\\(|\\)|\\[|\\]", ""));
                        }
                        String[] waitMessage = merge.toString().split(",");
                        if (waitMessage.length != 3) {
                            System.err.println("Client-" + user.getUID() + ":" + "错误的等待信息");
                        }
                    } else if (message.indexOf("get-attack[") == 0) {
                        Matcher matcher = compile.matcher(message);// "get-attack[" + userUID[0] + "],command=[game],send=[请求对战];";
                        ArrayList<String> arrayList = new ArrayList<>();
                        while (matcher.find()) {
                            arrayList.add(matcher.group().replaceAll("\\(|\\)|\\[|\\]", ""));
                        }
                        if ("请求对战".equals(arrayList.get(2)) && "game".equals(arrayList.get(1))) {
                            System.out.println("是否同意与"+arrayList.get(0)+"对战?(Y/N)");
                            String str = new Scanner(System.in).next();
                            if ("Y".equalsIgnoreCase(str)) {
                                System.out.println("同意对战!");
                                sendCommand("newGame={write=[" + arrayList.get(0) + "],black=[" + user.getUID() + "]}");
                            } else {
                                System.out.println("拒绝对战!");
                                sendCommand("errorGame={user=["+arrayList.get(0)+"],send=["+user.getUID()+"拒绝了对战]}");
                            }
                        }

                    }
                    //else if("command:Server!sendUserList".equals(message)){

                    // }

                }
            } catch (SocketException e) {
                System.err.println("Client-" + user.getUID() + ":" + "与服务器断开了连接");
                break;
            } catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }

        }
    }

    public void sendCommand(String command) throws IOException {//写入命令--命令:客户端! (命令指令)
        dos.writeUTF("command-game:" + command + ";");//写入命令--命令:客户端!
        // 开启游戏对局 newGame={write=[(userUID2)],black=[(userUID1)]}
        // 拒绝对战 errorGame={user=[(userUID1)],send=[(userUID2)拒绝了对战]}
        // 请求对战 attackUser:[(UID),(attackUserUID)]
    }

    public User getUser() {
        return user;
    }

    public DataInputStream getDis() {
        return dis;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }
}
