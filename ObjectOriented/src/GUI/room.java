package GUI;


import Game.Core;
import Game.PlayerTime;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class room extends JPanel implements ActionListener {//由于申请对战的人是黑棋 所以需要再修改
    //分割界面
    public static JSplitPane jsp1 = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
    JSplitPane jsp2 = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
    JSplitPane jsp3 = new JSplitPane(JSplitPane.VERTICAL_SPLIT);

    //选项卡
    JTabbedPane jtp = new JTabbedPane();
    JTabbedPane jtp1 = new JTabbedPane();
    JTabbedPane jtp2 = new JTabbedPane();
    JTabbedPane jtp3 = new JTabbedPane();

    JLabel userName1 = new JLabel();
    JLabel userName2 = new JLabel();
    JLabel userImg1 = new JLabel();
    JLabel userImg2 = new JLabel();
    JLabel time1 = new JLabel("本步剩余时间：");
    JLabel time2 = new JLabel("本步剩余时间：");
    JLabel title = new JLabel("<<<< 五子棋游戏 房间 >>>>");

    JButton send = new JButton("发送");
    JButton exit = new JButton("退出");
    JButton restart = new JButton("重新开始");
    JButton summation = new JButton("求和");
    JButton admit = new JButton("认输");
    JButton regret = new JButton("悔棋");

    JPanel One = new JPanel();
    JPanel Two = new JPanel();
    JPanel Three = new JPanel();
    JPanel Four = new JPanel();

    JTextArea jta = null;
    JTextField jtf = null;

    private Core core;
    private GameGUI gobang;

    public room(JTabbedPane jtp, ClientGUI gui) {
        core = new Core(19, 19);
        this.jtp = jtp;

        jsp1.setLeftComponent(jsp2);
        jsp2.setRightComponent(jsp3);
        //设置分隔条大小
        jsp1.setDividerSize(2);
        jsp2.setDividerSize(2);
        jsp3.setDividerSize(2);
        //设置分隔条位置
        jsp1.setDividerLocation(200);
        jsp2.setDividerLocation(200);
        jsp3.setDividerLocation(200);
        //设置选项卡名字
        jtp1.addTab("对手", One);
        jtp2.addTab("自己", Two);
        jtp3.addTab("聊天", Three);
        //第一个界面
        One.setLayout(new BorderLayout());//设置边框式布局
        JPanel North1 = new JPanel(); //One界面的北部
        userImg1 = new JLabel(new ImageIcon("./res/face/1-1.gif"));
        userName1 = new JLabel("name1");
        North1.add(userImg1);
        North1.add(userName1);
        One.add(North1, "North");
        One.add(time1, "West");
        //玩家1时间
        PlayerTime playerTime1=new PlayerTime(true);
        playerTime1.setBounds(100,500,200,100);
        playerTime1.start_time();
        playerTime1.setOpaque(false);
        One.add(playerTime1,"East");
        jsp2.setLeftComponent(jtp1);

        //第二个界面
        Two.setLayout(new BorderLayout());//设置边框式布局
        JPanel North2 = new JPanel(); //One界面的北部

        userImg2 = new JLabel(new ImageIcon(gui.getClient().getUser().getPassword()));
        userName2 = new JLabel(gui.getClient().getUser().getUID());
        North2.add(userImg2);
        North2.add(userName2);
        Two.add(North2, "North");
        //玩家2时间
        PlayerTime playerTime2=new PlayerTime(true);
        playerTime2.setBounds(100,500,200,100);
        playerTime2.start_time();
        playerTime2.setOpaque(false);
        Two.add(time2, "West");
        Two.add(playerTime2,"East");
        //玩家2时间

        jsp3.setLeftComponent(jtp2);

        //第三个界面
        Three.setLayout(new BorderLayout());
        JPanel South3 = new JPanel(new BorderLayout()); //Three界面南部
        jta = new JTextArea();
        jtf = new JTextField();
        South3.add(jtf, "Center");
        South3.add(send, "East");
        Three.add(jta, "Center");
        Three.add(South3, "South");
        jsp3.setRightComponent(jtp3);

        //第四个界面
        Four.setLayout(new BorderLayout());
        JPanel South4 = new JPanel(); //第四个界面南部
        South4.setBackground(Color.gray);

        Four.add(South4, "South");
        Four.add(title, "North");
        jsp1.setRightComponent(Four);
        //棋盘
        gobang = new GameGUI(core);
        Four.add(gobang, "Center");
        South4.add(exit);
        South4.add(restart);
        South4.add(regret);
        South4.add(admit);
        South4.add(summation);
        //绑定监听
        exit.addActionListener(this);
        restart.addActionListener(this);
        regret.addActionListener(this);
        admit.addActionListener(this);
        summation.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == exit) {
            jtp.remove(jsp1);
            GateWindows.btnseat[0].setIcon(new ImageIcon("./src/gobang/img/none.gif"));//还需要修改
        } else if (e.getSource() == restart) {//重新开始
            core.Restart();
            this.repaint();
        } else if (e.getSource() == summation) {//求和
            Object[] options = {"确认", "取消"};
            int n = JOptionPane.showOptionDialog(null, "确认申请和棋?", "申请和棋", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[0]);
            options = new Object[]{"确认"};
            if (n == 0) {
                core.Restart();
                gobang.repaint();
                JOptionPane.showOptionDialog(null, "平局,开始新对局!", "和棋成功", JOptionPane.YES_NO_OPTION, JOptionPane.CLOSED_OPTION, null, options, options[0]);
            } else if (n == 1) {
                JOptionPane.showOptionDialog(null, "和棋失败,进行对局", "和棋失败", JOptionPane.YES_NO_OPTION, JOptionPane.ERROR_MESSAGE, null, options, options[0]);
            }
        } else if (e.getSource() == regret) {//悔棋
            core.RetChess();
            if (gobang.getVar() == 1) {
                gobang.setVar(2);
            } else if (gobang.getVar() == 2) {
                gobang.setVar(1);
            }
            gobang.repaint();
        }else if(e.getSource()== admit){//认输
            Object[] options = {"确认","取消"};
            String str=(gobang.getVar()==1)?"白棋":"黑棋";
            int n = JOptionPane.showOptionDialog(null,str+":确认申请认输吗?","申请认输",JOptionPane.YES_NO_OPTION,JOptionPane.QUESTION_MESSAGE, null,options,options[1]);
            if(n==0) {
                core.Restart();
                gobang.repaint();
                options = new Object[]{"确认"};
                JOptionPane.showOptionDialog(null,str+"已经认输,开始新对局!","确认认输",JOptionPane.YES_NO_OPTION,JOptionPane.CLOSED_OPTION, null,options,options[0]);
            }
        }
    }
}