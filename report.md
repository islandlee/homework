理解文件访问的执行过程

参考同学的修改方式输出：
sysfile_read begin
file_read begin
file_read file acquired
vop_read(sfs_read) begin
sfs_io begin
sfs_io_nolock begin
sfs_io_nolock begin reading (by sfs_rblock or sfs_rbuf)
sfs_rbuf begin
sfs_rwblock_nolock begin
sfs_rwblock_nolock iobuf_init
disk0_io begin
disk0_read_blks_nolock begin
ide_read_secs begin
ide_read_secs call insl to read from disk
ide_read_secs end
disk0_read_blks_nolock end
disk0_io end
sfs_rwblock_nolock end
sfs_rbuf end
sfs_io_nolock end
sfs_io end
file_read file released
file_read end
sysfile_read end

sysfile_read begin
file_read begin
file_read file acquired
vop_read(sfs_read) begin
sfs_io begin
sfs_io_nolock begin
sfs_io_nolock begin reading (by sfs_rblock or sfs_rbuf)
sfs_rblock begin
sfs_rwblock begin
sfs_rwblock_nolock begin
sfs_rwblock_nolock iobuf_init
disk0_io begin
disk0_read_blks_nolock begin
ide_read_secs begin
ide_read_secs call insl to read from disk
ide_read_secs end
disk0_read_blks_nolock end
disk0_io end
sfs_rwblock_nolock end
sfs_rwblock end
sfs_rblock end
sfs_io_nolock end
sfs_io end
file_read file released
file_read end
sysfile_read end



调用过程:
(1)syscall
(2)sysfile_read
(3)file_read
(4)vop_read
(5)sfs_io
(6)sfs_io_nolock
(7)sfs_rbuf / sfs_rblock->sfs_rwblock (8)sfs_rwblock_nolock
(9)disk0_io
(10)disk0_read_blks_nolock
(11)ide_read_secs
(12)insl