# brctl & ip 命令

## brctl

### 网桥的概念

摘自百度百科：

        网桥（Bridge）是早期的两端口二层网络设备，用来连接不同网段。

        网桥是一种对帧进行转发的技术，根据 MAC 分区块，可隔离碰撞。网桥将网络的多个网段在数据链路层连接起来。

        网桥也叫桥接器，是连接两个局域网的一种存储/转发设备，它能将一个大的 LAN 分割为多个网段，或将两个以上的 LAN 互联为一个逻辑 LAN，使 LAN 上的所有用户都可访问服务器。

        扩展局域网最常见的方法是使用网桥。最简单的网桥有两个端口，复杂些的网桥可以有更多的端口，实现各个端口之间的互通。网桥的每个端口与一个网段相连。

这边先理解一下这几个名词，摘自：《子网、局域网、网段的关系》，更详细的说明可以访问该链接：

- 局域网  
        数据链路层的概念，指二层可达的网络（也就是不需要三层设备，如路由器，也能到达的网络），通俗得讲就是小范围的网络。
- 子网
        子网是网络层的概念，和局域网没有直接的关系，是把一个 IP 网络划分为几个小范围的网络，但是在平时不要求精确性的时候，局域网可以对应子网，也就是说，子网也是二层可达，子网之间需要三层设备。
- 网段
        是物理层的定义，使用同一物理层设备（传输介质，中继器，集线器等）能够直接通讯。

同一网段和不同网段：

- 使用同一物理层的设备之间必然通过相同的传输介质直接相互连接，如交叉双绞线直接连接的两台主机，是一个网段。
- 两组其传输介质并非直接相连的网络设备，如果它们的传输介质通过工作在物理层的扩展设备如中继器和集线器等转接连接，则仍然被视为同一物理层中的设备，是一个网段。
- 工作在数据链路层或更高层的设备如网桥、交换机、路由器等等，由它们连接起来的两组设备仍然分别处于各自独立的物理层，是两个网段。

### 管理网桥的命令

Linux中通过 brctl 命令管理以太网网桥。

通过 brctl --help 获取到 brctl 命令的使用方法

        Usage: brctl COMMAND [BRIDGE [INTERFACE]]

        Manage ethernet bridges

        Commands:
                show                    Show a list of bridges
                addbr BRIDGE            Create BRIDGE
                delbr BRIDGE            Delete BRIDGE
                addif BRIDGE IFACE      Add IFACE to BRIDGE
                delif BRIDGE IFACE      Delete IFACE from BRIDGE
                setageing BRIDGE TIME           Set ageing time
                setfd BRIDGE TIME               Set bridge forward delay
                sethello BRIDGE TIME            Set hello time
                setmaxage BRIDGE TIME           Set max message age
                setpathcost BRIDGE COST         Set path cost
                setportprio BRIDGE PRIO         Set port priority
                setbridgeprio BRIDGE PRIO       Set bridge priority
                stp BRIDGE [1/yes/on|0/no/off]  STP on/off

1. 显示已有的网桥列表

    > brctl show

2. 创建网桥

    > brctl addbr bridge_name

3. 删除网桥

    > brctl delbr briage_name

4. 增加网桥中的接口

    > brctl addif bridge_name interface_name

5. 删除网桥中的接口

    > brctl delif bridge_name interface_name

        brctl addbr bridge的名称                    #添加bridge；

        brctl delbr bridge的名称                    #删除bridge；

        brctl addif bridge的名称 device的名称(网卡)   #添加接口到bridge；

        brctl delif bridge的名称 device的名称        #从bridge中删除接口

        brctl setageing bridge的名称 时间            #设置老化时间，即生存周期

        brctl setbridgeprio bridge的名称 优先级      #设置bridge的优先级

        brctl setfd bridge的名称 时间                #设置bridge转发延迟时间

        brctl sethello bridge的名称 时间             #设置hello时间

        brctl setmaxage bridge的名称 时间            #设置消息的最大生命周期

        brctl setpathcost bridge的名称 端口 权重      #设置路径的权值

        brctl setportprio bridge的名称 端口 优先级    #设置端口的优先级

        brctl show                                  #显示bridge列表

        brctl showmacs bridge的名称                  #显示MAC地址

        brctl showstp bridge的名称                   #显示bridge的stp(生成树协议)信息

        brctl stp bridge的名称 {on|off}              #开/关stp

## ip命令

Linux ip 命令与 ifconfig 命令类似，但比 ifconfig 命令更加强大，主要功能是用于显示或设置网络设备。

ip 命令是 Linux 加强版的的网络配置工具，用于代替 ifconfig 命令。

语法
> ip [ OPTIONS ] OBJECT { COMMAND | help }

OBJECT 为常用对象，值可以是以下几种：

> OBJECT={ link | addr | addrlabel | route | rule | neigh | ntable | tunnel | maddr | mroute | mrule | monitor | xfrm | token }

常用对象的取值含义如下：

    link：网络设备
    address：设备上的协议（IP或IPv6）地址
    addrlabel：协议地址选择的标签配置
    route：路由表条目
    rule：路由策略数据库中的规则
    OPTIONS 为常用选项，值可以是以下几种：

>OPTIONS={ -V[ersion] | -s[tatistics] | -d[etails] | -r[esolve] | -h[uman-readable] | -iec | -f[amily] { inet | inet6 | ipx | dnet | link } | -o[neline] | -t[imestamp] | -b[atch] [filename] | -rc[vbuf] [size] }

常用选项的取值含义如下：

    -V：显示命令的版本信息；
    -s：输出更详细的信息；
    -f：强制使用指定的协议族；
    -4：指定使用的网络层协议是IPv4协议；
    -6：指定使用的网络层协议是IPv6协议；
    -0：输出信息每条记录输出一行，即使内容较多也不换行显示；
    -r：显示主机时，不使用IP地址，而使用主机的域名。
help 为该命令的帮助信息。

实例

    ip link show                     # 显示网络接口信息
    ip link set eth0 up             # 开启网卡
    ip link set eth0 down            # 关闭网卡
    ip link set eth0 promisc on      # 开启网卡的混合模式
    ip link set eth0 promisc off    # 关闭网卡的混个模式
    ip link set eth0 txqueuelen 1200 # 设置网卡队列长度
    ip link set eth0 mtu 1400        # 设置网卡最大传输单元
    ip addr show     # 显示网卡IP信息
    ip addr add 192.168.0.1/24 dev eth0 # 设置eth0网卡IP地址192.168.0.1
    ip addr del 192.168.0.1/24 dev eth0 # 删除eth0网卡IP地址

    ip route show # 显示系统路由
    ip route add default via 192.168.1.254   # 设置系统默认路由
    ip route list                 # 查看路由信息
    ip route add 192.168.4.0/24  via  192.168.0.254 dev eth0 # 设置192.168.4.0网段的网关为192.168.0.254,数据走eth0接口
    ip route add default via  192.168.0.254  dev eth0        # 设置默认网关为192.168.0.254
    ip route del 192.168.4.0/24   # 删除192.168.4.0网段的网关
    ip route del default          # 删除默认路由
    ip route delete 192.168.1.0/24 dev eth0 # 删除路由

### ip rule

#### 简介

在某些情况下，我们不只是需要通过数据包的目的地址决定路由，可能还需要通过其他一些域：源地址、IP协议、传输层端口甚至数据包的负载。这就叫做：策略路由(policy routing)。

基于策略的路由比传统路由在功能上更强大，使用更灵活，它使网络管理员不仅能够根据目的地址而且能够根据报文大小、应用或IP源地址等属性来选择转发路径。简单地来说，linux系统有多张路由表，而路由策略会根据一些条件，将路由请求转向不同的路由表。例如源地址在某些范围走路由表A，另外的数据包走路由表，类似这样的规则是有路由策略rule来控制。

在linux系统中，一条路由策略rule主要包含三个信息，即rule的优先级，条件，路由表。其中rule的优先级数字越小表示优先级越高，然后是满足什么条件下由指定的路由表来进行路由。在linux系统启动时，内核会为路由策略数据库配置三条缺省的规则，即rule 0，rule 32766， rule 32767（数字是rule的优先级）

![ip rule](./pic/iprule.png)

- rule 0 ：匹配任何条件的数据包，查询路由表local（table id = 255）。rule 0非常特殊，不能被删除或者覆盖。 查询路由表local(ID 255) | 路由表local 是一个特殊的路由表，包含对于本地和广播地址的高优先级控制路由。
- rule 32766：匹配任何条件的数据包，查询路由表main(ID 254)，路由表main(ID 254)是一个通常的表，包含所有的无策略路由。平时使用route add添加的路由都是加到这个表里面的。
- rule 32767：匹配任何条件的数据包，查询路由表default(ID 253)，路由表default(ID 253)是一个空表，它是为一些后续处理保留的。对于前面的缺省策略没有匹配到的数据包，系统使用这个策略进行处理这个规则也可以删除。

        备注：在linux系统中是按照rule的优先级顺序依次匹配。假设系统中只有优先级为0，32766及32767这三条规则。那么系统首先会根据规则0在本地路由表里寻找路由，如果目的地址是本网络，或是广播地址的话，在这里就可以找到匹配的路由；如果没有找到路由，就会匹配下一个不空的规则，在这里只有32766规则，那么将会在主路由表里寻找路由；如果没有找到匹配的路由，就会依据32767规则，即寻找默认路由表；如果失败，路由将失败。

#### 用法

>Usage: ip rule [ list | add | del ] SELECTOR ACTION  
SELECTOR := [ from PREFIX 数据包源地址] [ to PREFIX 数据包目的地址] [ tos TOS 服务类型][ dev STRING 物理接口]  
            [ pref NUMBER 优先级 ] [fwmark MARK iptables 标签]  
ACTION := [ table TABLE_ID 指定所使用的路由表] [ nat ADDRESS 网络地址转换][ prohibit 丢弃该表| reject 拒绝该包| unreachable 丢弃该包]  
[ flowid CLASSID ]  
TABLE_ID := [ local | main | default | NUMBER ]

SELECTOR具体参数如下：

    From — 源地址
    To — 目的地址（这里是选择规则时使用，查找路由表时也使用）
    Tos — IP包头的TOS（type of sevice）域
    Dev — 物理接口
    Fwmark — 防火墙参数

ACTION动作：

    Table 指明所使用的表
    Nat 透明网关
    Action prohibit 丢弃该包，并发送 COMM.ADM.PROHIITED的ICMP信息
    Reject 单纯丢弃该包
    Unreachable丢弃该包， 并发送 NET UNREACHABLE的ICMP信息

#### 增加策略

1.指定优先级

第一条命令将向规则链增加一条规则，规则匹配的对象是所有的数据包，动作是选用路由表1的路由，这条规则的优先级是32800.

第二条命令将向规则链增加一条规则，规则匹配的对象是IP为192.168.3.112, tos等于0x10的包，使用路由表2,这条规则的优先级是32801,动作是丢弃。

    root@debian:~# ip rule add from 0/0 table 1 pref 32800  
    root@debian:~# ip rule add from 192.168.3.112/32 tos 0x10 table 2 pref 32801 prohibit  
    root@debian:~# ip rule  
    0:      from all lookup local  
    32766:  from all lookup main  
    32767:  from all lookup default  
    32800:  from all lookup 1  
    32801:  from 192.168.3.112 tos 0x10 lookup 2 prohibit  

2.不指定优先级  

而添加策略时，是可以不指定pref 优先级的，那么系统就会默认创建rule的ID，在main的前面往前移一位。

    root@debian:~# ip rule  add from 171.43.122.52 tab 200  
    root@debian:~# ip rule  
    0:      from all lookup local  
    32765:  from 171.43.122.52 lookup 200  
    32766:  from all lookup main  
    32767:  from all lookup default  

3.iptables 的 set-mark功能

还可以借助iptables来实现其他不一样的功能。

使用Netfilter的managle机制针对特定的数据包设置MARK值，在此将3389端口的数据包的MARK值设置为1，然后将fwmark 1的规则应用到ip rule上即可。这样就可以实现特定程序的流量走不同的路线。

    root@debian:~# iptables -t mangle -A OUTPUT -p tcp --dport 8080 -j MARK --set-mark 1
    root@debian:~# ip rule add fwmark 1 table 20 pref 20
    root@debian:~# ip route add default via 171.43.122.52 table 20
    root@debian:~# ip rule
    0:      from all lookup local
    20:     from all fwmark 0x1 lookup 20
    32765:  from 171.43.122.52 lookup 200
    32766:  from all lookup main
    32767:  from all lookup default
    root@debian:~# iptables -t mangle -nvL
    Chain PREROUTING (policy ACCEPT 0 packets, 0 bytes)
    pkts bytes target     prot opt in     out     source               destination

    Chain INPUT (policy ACCEPT 0 packets, 0 bytes)
    pkts bytes target     prot opt in     out     source               destination

    Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
    pkts bytes target     prot opt in     out     source               destination

    Chain OUTPUT (policy ACCEPT 0 packets, 0 bytes)
    pkts bytes target     prot opt in     out     source               destination
        0     0 MARK       tcp  --  *      *       0.0.0.0/0            0.0.0.0/0            tcp dpt:8080 MARK set 0x1

    Chain POSTROUTING (policy ACCEPT 0 packets, 0 bytes)
    pkts bytes target     prot opt in     out     source               destination

### ifconfig命令

语法

>ifconfig [网络设备][down up -allmulti -arp -promisc][add<地址>][del<地址>][<hw<网络设备类型><硬件地址>][io_addr<I/O地址>][irq<IRQ地址>][media<网络媒介类型>][mem_start<内存地址>][metric<数目>][mtu<字节>][netmask<子网掩码>][tunnel<地址>][-broadcast<地址>][-pointopoint<地址>][IP地址]

参数说明：

    add<地址> 设置网络设备IPv6的IP地址。
    del<地址> 删除网络设备IPv6的IP地址。
    down 关闭指定的网络设备。
    <hw<网络设备类型><硬件地址> 设置网络设备的类型与硬件地址。
    io_addr<I/O地址> 设置网络设备的I/O地址。
    irq<IRQ地址> 设置网络设备的IRQ。
    media<网络媒介类型> 设置网络设备的媒介类型。
    mem_start<内存地址> 设置网络设备在主内存所占用的起始地址。
    metric<数目> 指定在计算数据包的转送次数时，所要加上的数目。
    mtu<字节> 设置网络设备的MTU。
    netmask<子网掩码> 设置网络设备的子网掩码。
    tunnel<地址> 建立IPv4与IPv6之间的隧道通信地址。
    up 启动指定的网络设备。
    -broadcast<地址> 将要送往指定地址的数据包当成广播数据包来处理。
    -pointopoint<地址> 与指定地址的网络设备建立直接连线，此模式具有保密功能。
    -promisc 关闭或启动指定网络设备的promiscuous模式。
    [IP地址] 指定网络设备的IP地址。
    [网络设备] 指定网络设备的名称。

## route命令

### route简介

route命令用来显示并设置Linux内核中的网络路由表，route命令设置的路由主要是静态路由。
要注意的是，直接在命令行下执行route命令来添加路由，不会永久保存，当网卡重启或者机器重启之后，该路由就失效了。可以在/etc/rc.local中添加route命令来保证该路由设置永久有效

### route语法

route [选项] [参数]

1. 选项

        -A  设置地址类型  
        -C  打印将Linux核心的路由缓存  
        -v  详细信息模式  
        -n  不执行DNS反向查找，直接显示数字形式的IP地址
        -e  netstat格式显示路由表
        -net  到一个网络的路由表
        -hostB  到一个主机的路由表

2. 参数：  

        add  增加指定的路由记录
        del  删除指定的路由记录
        target  目的网络或目的主机
        netmask  为添加的路由指定网络掩码
        gw  设置默认网关
        mss  设置TCP的最大区块长度（MSS），单位MB，默认值为536
        window  指定通过路由表的TCP连接的TCP窗口大小
        dev  路由记录所表示的网络接口

3. 输出信息：

        Destination：目标网络或目标主机。
        Gateway：网关地址或'*'(如未设)。
        Genmask：目标网络的子网掩码；'255.255.255.255'为主机，'0.0.0.0'为缺省路由。
        Flags可能出现的标志有：
        U (route is up) 路由正常
        H (target is a host) 主机路由
        G (use gateway) 使用网关的间接路由
        R (reinstate route for dynamic routing) 为动态选路恢复路由
        D (dynamically installed by daemon o redirect)该路由由选路进程或重定向动态创建
        M (modified from routing daemon or rederict)该路由已由选路进程或重定向修改
        ! (reject route) 阻塞路由
            Metric：通向目标的距离(通常以跳来计算)。新内核不使用此概念，而选路进程可能会用。
        Ref：使用此路由的活动进程个数(Linux内核并不使用)。
        Use：查找此路由的次数。根据-F和-C的使用，此数值是路由缓存的损失数或采样数。
        Iface：使用此路由发送分组的接口。
