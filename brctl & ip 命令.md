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
