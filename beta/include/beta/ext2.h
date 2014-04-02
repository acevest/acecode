/*
 *--------------------------------------------------------------------------
 *   File Name:	ext2.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct  2 23:37:40 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_EXT2_H
#define	_EXT2_H

#include<beta/types.h>

#define	EXT2_BAD_INO		1
#define	EXT2_ROOT_INO		2
#define	EXT2_BOOT_LOADER_INO	5
#define	EXT2_UNDEL_DIR_INO	6

#define	EXT2_MIN_BLOCK_SIZE	1024
#define	EXT2_MAX_BLOCK_SIZE	4096
#define	EXT2_MIN_BLOCK_LOG_SIZE	10

#define	EXT2_SB			(&ext2_sb)
#define	EXT2_SECT		(ext2_start_sect)

#ifndef	EXT2_SB
#error "Please define EXT2_SB"
#endif

#define	EXT2_BLOCK_SIZE		(EXT2_MIN_BLOCK_SIZE << 	\
				(EXT2_SB)->s_log_block_size)

#define	EXT2_SECT_PER_BLOCK	(EXT2_BLOCK_SIZE/512)

#define	EXT2_BLOCK_SIZE_BITS	((EXT2_SB)->s_log_block_size + 10)
#define	EXT2_INODE_SIZE		((EXT2_SB)->s_inode_size)
#define	EXT2_INODES_PER_BLOCK	(EXT2_BLOCK_SIZE/EXT2_INODE_SIZE)
#define	EXT2_FIRST_INO		((EXT2_SB)->s_first_ino)
#define	EXT2_FIRST_BLOCK_ID	(EXT2_BLOCK_SIZE == 1024)

#define	EXT2_BLOCKS_PER_GROUP	((EXT2_SB)->s_blocks_per_group)
#define	EXT2_DESC_PER_BLOCK	((EXT2_SB)->s_desc_per_block)
#define	EXT2_INODES_PER_GROUP	((EXT2_SB)->s_inodes_per_group)
#define	EXT2_INODES_COUNT	((EXT2_SB)->s_inodes_count)

/*
 * ------------------------------------------------------------------------
 *  EXT2 FILE SYSTEM PART
 * ------------------------------------------------------------------------
 */
struct ext2_superblock
{
	__le32	s_inodes_count;		/* Inodes count */
	__le32	s_blocks_count;		/* Blocks count */
	__le32	s_r_blocks_count;	/* Reserved blocks count */
	__le32	s_free_blocks_count;	/* Free blocks count */
	__le32	s_free_inodes_count;	/* Free inodes count */
	__le32	s_first_data_block;	/* First Data Block */
	__le32	s_log_block_size;	/* Block size */
	__le32	s_log_frag_size;	/* Fragment size */
	__le32	s_blocks_per_group;	/* # Blocks per group */
	__le32	s_frags_per_group;	/* # Fragments per group */
	__le32	s_inodes_per_group;	/* # Inodes per group */
	__le32	s_mtime;		/* Mount time */
	__le32	s_wtime;		/* Write time */
	__le16	s_mnt_count;		/* Mount count */
	__le16	s_max_mnt_count;	/* Maximal mount count */
	__le16	s_magic;		/* Magic signature */
	__le16	s_state;		/* File system state */
	__le16	s_errors;	/* Behaviour when detecting errors */
	__le16	s_minor_rev_level; 	/* minor revision level */
	__le32	s_lastcheck;		/* time of last check */
	__le32	s_checkinterval;	/* max. time between checks */
	__le32	s_creator_os;		/* OS */
	__le32	s_rev_level;		/* Revision level */
	__le16	s_def_resuid;	/* Default uid for reserved blocks */
	__le16	s_def_resgid;	/* Default gid for reserved blocks */
	/*
	 * These fields are for EXT2_DYNAMIC_REV superblocks only.
	 *
	 * Note: the difference between the compatible feature set and
	 * the incompatible feature set is that if there is a bit set
	 * in the incompatible feature set that the kernel doesn't
	 * know about, it should refuse to mount the filesystem.
	 * 
	 * e2fsck's requirements are more strict; if it doesn't know
	 * about a feature in either the compatible or incompatible
	 * feature set, it must abort and not try to meddle with
	 * things it doesn't understand...
	 */
	__le32	s_first_ino; 		/* First non-reserved inode */
	__le16	s_inode_size; 		/* size of inode structure */
	__le16	s_block_group_nr; /* block group # of this superblock */
	__le32	s_feature_compat; 	/* compatible feature set */
	__le32	s_feature_incompat; 	/* incompatible feature set */
	__le32	s_feature_ro_compat; /* readonly-compatible feature set */
	__u8	s_uuid[16];		/* 128-bit uuid for volume */
	char	s_volume_name[16]; 	/* volume name */
	char	s_last_mounted[64]; 	/* directory where last mounted */
	__le32	s_algorithm_usage_bitmap; /* For compression */
	/*
	 * Performance hints.  Directory preallocation should only
	 * happen if the EXT2_COMPAT_PREALLOC flag is on.
	 */
	__u8	s_prealloc_blocks;/* Nr of blocks to try to preallocate*/
	__u8	s_prealloc_dir_blocks;/* Nr to preallocate for dirs */
	__le16	s_padding1;
	/*
	 * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
	 */
	__u8	s_journal_uuid[16];	/* uuid of journal superblock */
	__le32	s_journal_inum;		/* inode number of journal file */
	__le32	s_journal_dev;		/* device number of journal file */
	__le32	s_last_orphan;	/* start of list of inodes to delete */
	__le32	s_hash_seed[4];		/* HTREE hash seed */
	__u8	s_def_hash_version;	/* Default hash version to use */
	__u8	s_reserved_char_pad;
	__le16	s_reserved_word_pad;
	__le32	s_default_mount_opts;
 	__le32	s_first_meta_bg; 	/* First metablock block group */
	__le32	s_reserved[190];/* Padding to the end of the block */
};


struct ext2_group_desc
{
	__le32	bg_block_bitmap;
	__le32	bg_inode_bitmap;
	__le32	bg_inode_table;
	__le16	bg_free_blocks_count;
	__le16	bg_free_inodes_count;
	__le16	bg_used_dirs_count;
	__le16	bg_pad;
	__le32	bg_reserved[3];
};

#define	EXT2_NDIR_BLOCKS	(12)
#define	EXT2_IND_BLOCK		(EXT2_NDIR_BLOCKS)
#define	EXT2_DIND_BLOCK		(EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK		(EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS		(EXT2_TIND_BLOCK + 1)


struct ext2_inode
{
	__le16	i_mode;
	__le16	i_uid;
	__le32	i_size;
	__le32	i_atime;
	__le32	i_ctime;
	__le32	i_mtime;
	__le32	i_dtime;
	__le16	i_gid;
	__le16	i_links_count;
	__le32	i_blocks;
	__le32	i_flags;
	__le32	i_reserved1;
	__le32	i_block[EXT2_N_BLOCKS];
	__le32	i_generation;
	__le32	i_file_acl;
	__le32	i_dir_acl;
	__le32	i_faddr;
	__u8	i_frag;
	__u8	i_fsize;
	__u16	i_pad1;
	__le16	i_uid_high;
	__le16	i_gid_high;
	__u32	i_reserved2;
};


#define	EXT2_NAME_LEN	255
struct ext2_dir_entry
{
	__le32	inode;
	__le16	rec_len;
	__u8	name_len;
	__u8	file_type;
	char	name[EXT2_NAME_LEN];
};

enum
{
	EXT2_FT_UNKNOWN,
	EXT2_FT_REG_FILE,
	EXT2_FT_DIR,
	EXT2_FT_CHRDEV,
	EXT2_FT_BLKDEV,
	EXT2_FT_FIFO,
	EXT2_FT_SOCK,
	EXT2_FT_SYMLINK,
	EXT2_FT_MAX
};


#define	EXT2_DIR_PAD			4
#define	EXT2_DIR_ROUND			(EXT2_DIR_PAD-1)
#define	EXT2_DIR_REC_LEN(name_len)	(((name_len)+8+EXT2_DIR_ROUND) & \
						~EXT2_DIR_ROUND)
#define	EXT2_MAX_REC_LEN		((1<<16)-1)

#endif //_EXT2_H
