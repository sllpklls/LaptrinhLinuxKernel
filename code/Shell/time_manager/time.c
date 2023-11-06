#timedatectl set-ntp off
#!/bin/sh
 command=$1
if [ -z $command ]
     then echo "Chua nhap chuc nang"
 fi
 if [ $command = "info" ]
     then TZ="$2" date
 fi
 
 if [ $command = "set-time" ]
     then
         if [ `whoami` != "root" ]
             then
             echo 'Ban can phai chay lenh sudo de thay doi thoi gian'
             exit $E_NOTROOT
         fi
         echo "Xin hay nhap ngay theo dinh dang yyyy-mm-dd?"
         read new_date
         echo "Xin hay nhap ngay theo dinh dang hh:mm:ss?"
         read new_hour
         sudo timedatectl set-ntp off
         timedatectl set-time "$new_date $new_hour"
 fi
 if [ $command = "automatic" ]
     then
         if [ `whoami` != "root" ]
             then
             echo 'Ban can phai chay lenh sudo de thay doi thoi gian'
             exit $E_NOTROOT
         fi
         echo "Thoi gian dang duoc cap nhat tu dong”
         timedatectl set-ntp on
fi
