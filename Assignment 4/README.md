
# ZFS vs. ext4 Filesystem Experiment

## Installation

### 1. ZFS Installation  
1. **Install ZFS Filesystem:**  
   ```bash
   sudo apt install zfsutils-linux -y
   ```
2. **List Available Disks:**  
   Ensure that you select a disk with **at least 5 GB** of space, excluding the system disk (e.g., `/dev/sda`):  
   ```bash
   sudo fdisk -l
   ```
3. **Create a ZFS Pool:**  
   Replace `/dev/sdb` with your chosen disk:
   ```bash
   sudo zpool create zfs_pool /dev/sdb
   ```
4. **Enable Deduplication:**  
   ```bash
   sudo zfs set dedup=on zfs_pool
   ```
5. **Verify ZFS Pool Creation:**  
   List the pool:
   ```bash
   sudo zpool status
   ```
6. **Anchor for Workloads:**  
   ZFS pool is mounted at `/zfs_pool`.

### 2. ext4 Setup  
1. **Use a Virtual Disk File (Optional):**  
   Create a 5GB disk image:
   ```bash
   sudo dd if=/dev/zero of=/zfs_disk.img bs=1M count=5120
   ```
2. **Set up a Loop Device:**  
   ```bash
   sudo losetup -fP /zfs_disk.img
   ```
3. **Format the Disk as ext4:**  
   ```bash
   sudo mkfs.ext4 /dev/loopXp1
   ```
4. **Mount the ext4 Partition:**  
   ```bash
   sudo mkdir -p /mnt/virtual_ext4
   sudo mount /dev/loopXp1 /mnt/virtual_ext4
   ```
5. **Verify the Mount:**  
   ```bash
   df -h | grep virtual_ext4
   ```
6. **Anchor for Workloads:**  
   ext4 is mounted at `/mnt/virtual_ext4`.

## Finding the Anchors  
1. **ZFS Anchor:**  
   The anchor is the **ZFS pool directory**: `/zfs_pool`
2. **ext4 Anchor:**  
   The anchor is the **ext4 mount point**: `/mnt/virtual_ext4`

## Running Workloads  
1. **Add workload1 and workload2** to the Vdbench directory.  
2. **Navigate to Vdbench Directory:**
   ```bash
   cd /path/to/vdbench
   ```
3. **Run Workloads:**
   - **For ZFS:**  
     ```bash
     ./vdbench workload1 anchor=/zfs_pool
     ```
   - **For ext4:**  
     ```bash
     ./vdbench workload1 anchor=/mnt/virtual_ext4
     ```

## Viewing Stats Workload 1  
1. **Summary Report:**  
   View the summary in `summary.html` inside the **Output folder** of the Vdbench directory.

2. **ZFS Stats:**
   - **Initial State:**  
     - Total Size: 4.50 GB  
     - Allocated: 108 KB  
     - Free Space: 4.50 GB  
     - Deduplication Ratio: 1.00x (No deduplication initially)  

   - **After Workload:**  
     - Allocated: 226 MB  
     - Free Space: 4.28 GB  
     - Deduplication Ratio: 2.00x (Storage halved for duplicate data)  


3. **ext4 Stats:**
   - **Before Workload:**  
     - Free Space: 4.9 GB  
     - Folder Content: 464 items, 471.9 MB total  

   - **After Workload:**  
     - Free Space: 4.4 GB  
     - Folder Content: Unchanged (464 items, 471.9 MB)  

## Workload 2: Large File Creation  
1. **Workload Configuration:**
   ```
   fsd=fsd1, anchor=$anchor, depth=0, width=1, files=2, size=1G
   fwd=fwd1, fsd=fsd1, operation=create, fileio=sequential, threads=2
   rd=rd1, fwd=fwd1, fwdrate=max, elapsed=30, interval=1
   ```
2. **Run on ZFS:**  
   ```bash
   ./vdbench workload2 anchor=/zfs_pool
   ```
   Time to create files: **29 seconds**
3. **Run on ext4:**  
   ```bash
   ./vdbench workload2 anchor=/mnt/virtual_ext4
   ```
   Time to create files: **7 seconds**

## Conclusion  
- **ZFS**: Efficient in saving space with **deduplication** but incurs performance overhead.  
- **ext4**: Optimized for large file creation with faster operations but uses more space due to metadata overhead.  

Choose ZFS for **storage efficiency** and ext4 for **performance with large files**.