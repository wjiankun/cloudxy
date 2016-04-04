# 基于ttylinux制作pv domU #

### 目的 ###
制作一个编译大家测试使用的pv domU(很多朋友没有支持vt的处理器，所以我们主要使用pv domU）

---

  1. 感谢我们的镜像提供者——ttylinux ：这是一个广泛应用于嵌入系统的小linux镜像，我们衷心感谢 Douglas Jerome（douglas@ttylinux.org）的无私奉献<br>
<ol><li>感谢stacklet提供Paravirtualized Kernel for Xen :<br>
<hr />
<h3>制作方法</h3>
</li></ol><ul><li>制作一个32M的镜像系统<br>
<ol><li>dd if=/dev/zero of=domU-32bit-FS.img bs=1M count=32<br>
</li><li>mkfs.ext3 domU-32bit-FS.img<br>
</li></ol></li><li>制作文件系统 —— 我们使用ttylinux-i486-8.0.img作为base文件系统(在download中有，直接去用就是了 - 之所以没直接用该镜像，是因为ttylinux-i486-8.0.img太小了，所以我们自己做了个32M的新文件系统，并且要把tty的东西导入到其中）<br>
<ol><li>sudo mount -o loop ttylinux-i486-8.0.img /mnt<br>
</li><li>mkdir domUdisk<br>
</li><li>sudo mount -o loop domU-32bit-FS.img domUdisk<br>
</li><li>cp -a mnt/<b>domUdisk/ -rf<br>
</li></ol></li><li>加入pv kernel 到domU-32bit-FS.img —— 我们使用 linux-2.6.35.8-xenU.x86.tar.bz2 版本的pv kernel<br>
<ol><li>tar xf linux-2.6.35.8-xenU.x86.tar.bz2  （从http://stacklet.com/download/kernel/list?architecture=x86下载,可能需要先注册）<br>
</li><li>cp boot/</b> domUdisk/ -rf<br>
</li><li>cp lib/<b>domUdisk/ -rf<br>
</li></ol></li><li>修改文件系统的相关配置 —— 见 <a href='http://stacklet.com/doc/kernel/howto-deploy-xen-domu-kernel'>http://stacklet.com/doc/kernel/howto-deploy-xen-domu-kernel</a> （稍有修改）<br>
<ol><li>mkdir domUdisk/boot<br>
</li><li>mkdir domUdisk/boot/grub<br>
</li><li>修改/boot/grub/grub.conf<br>
<pre><code>     title vmlinuz-2.6.35.4<br>
     root (hd0,0)<br>
     kernel /boot/vmlinuz-2.6.35.4 console=hvc0 root=/dev/xvda1 ro <br>
     写入domUdisk/boot/grub.conf<br>
</code></pre>
</li><li>修改/etc/fstab<br>
<pre><code>     /dev/xvda1   /           ext3     defaults,errors=remount-ro 0 0<br>
     tmpfs        /dev        tmpfs    noauto                     0 0<br>
     proc         /proc       proc     noauto                     0 0<br>
     none 	  /proc/xen   xenfs   defaults                    0 0<br>
     写入domUdisk/etc/fstab<br>
</code></pre>
</li><li>修改/etc/inittab<br>
<pre><code>     hvc0:2345:respawn:/sbin/getty 38400 hvc0 （可去掉tty相关记录了）<br>
     写入domUdisk/etc/inittab<br>
</code></pre>
</li><li>修改/etc/securetty<br>
<pre><code>     hvc0<br>
     写入/etc/securetty最后 （可去掉tty相关记录）<br>
</code></pre>
</li></ol></li><li>保存镜像<br>
<blockquote>umount domUdisk<br>
</blockquote></li><li>创建虚拟机启动配置 - pygrub.conf<br>
<pre><code>     memory = 512<br>
     name = "ttylinux"<br>
     bootloader = "/usr/bin/pygrub"<br>
     disk = ['tap2:aio:/home/kanghua/xen/domU-32bit-FS.img,xvda1,w'] <br>
     写入 pygrub.conf <br>
</code></pre>
<blockquote>注意：<br>
</blockquote><ol><li>/home/kanghua/xen/ 请替换为domU-32bit-FS.img的存储路径<br>
</li><li>网络，cpu等信息非必要信息，需要时自己补充。</li></ol></li></ul></b>

<ul><li>启动虚拟机<br>
<blockquote>sudo xm cr pygrub.con<br>
</blockquote></li><li>login虚拟机<br>
<blockquote>sudo xm console ttylinux (或者vmid)<br>
<pre><code>    注：<br>
    1.登陆名root,登陆密码password<br>
    2.如果登陆失败，请查看/var/log/syslog 日志和 /var/log/xen/xend.log 分析原因<br>
</code></pre></blockquote></li></ul>


上述需要文件，都已经上传到 <a href='http://code.google.com/p/cloudxy/downloads/'>http://code.google.com/p/cloudxy/downloads/</a>


<h3>问题</h3>
<ol><li>ttylinux 为了减少体积，使用busybox代替很多执行命令。但busybox有些地方和我们常用的执行命令有区别，请大家使用时注意（尤其写shell脚本时注意）。<br>
</li><li>你会发现hwclock执行错误，具体原因大概内核支持问题，有兴趣你可调查并解决之。<br>
</li><li>已经支持xenbus等，可操作/proc/xen/xenbus<br>
</li><li>该img主要目的是便于大家实验，因此功能难免有所不足。<br>
</li><li>抛砖引玉，制作pv domU方法很多，请理解为主，不要拘泥。<br>
</li><li>我们使用blktap2驱动vxda1,最好使用xen4.0以上的版本啦。</li></ol>

---<br>
wroten by 康华<br>
