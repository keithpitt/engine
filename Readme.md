### Building PhysicsFS

When building PhysicsFS, you have to disable unused archivers. This makes the file size smaller and fixes
a heap of Windows compilation issues.

```bash
cmake -DPHYSFS_ARCHIVE_ISO9660=0 -DPHYSFS_ARCHIVE_7Z=0 -DPHYSFS_ARCHIVE_GRP=0 -DPHYSFS_ARCHIVE_WAD=0 -DPHYSFS_ARCHIVE_HOG=0 -DPHYSFS_ARCHIVE_MVL=0 -DPHYSFS_ARCHIVE_QPAK=0 -DPHYSFS_ARCHIVE_SLB=0 -DPHYSFS_HAVE_CDROM_SUPPORT=0 -DPHYSFS_SUPPORTS_GRP=1 -DPHYSFS_BUILD_SHARED=1 -DPHYSFS_BUILD_TEST=0 ..
```
