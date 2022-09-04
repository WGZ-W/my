
查看磁盘的状态：  
```  
    $ lsblk  

或者  
  
    $ parted     /dev/nvme0n1  
```  

对磁盘进行操作：  
```  
    $ gdisk     /dev/nvme0n1  
```  

创建文件系统：  
```  
  $ mkfs.xfs    /dev/nvme0n1p8  
```  
