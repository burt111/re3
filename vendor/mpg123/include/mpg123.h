/*
	libmpg123: MPEG Audio Decoder library (version 1.26.3)

	copyright 1995-2015 by the mpg123 project
	free software under the terms of the LGPL 2.1
	see COPYING and AUTHORS files in distribution or http://mpg123.org
*/

#ifndef MPG123_LIB_H
#define MPG123_LIB_H

#include <fmt123.h>

/** \file mpg123.h The header file for the libmpg123 MPEG Audio decoder */

/** A macro to check at compile time which set of API functions to expect.
 * This should be incremented at least each time a new symbol is added
 * to the header.
 */
#define MPG123_API_VERSION 45

#ifndef MPG123_EXPORT
/** Defines needed for MS Visual Studio(tm) DLL builds.
 * Every public function must be prefixed with MPG123_EXPORT. When building 
 * the DLL ensure to define BUILD_MPG123_DLL. This makes the function accessible
 * for clients and includes it in the import library which is created together
 * with the DLL. When consuming the DLL ensure to define LINK_MPG123_DLL which
 * imports the functions from the DLL. 
 */
#ifdef BUILD_MPG123_DLL
/* The dll exports. */
#define MPG123_EXPORT __declspec(dllexport)
#else
#ifdef LINK_MPG123_DLL
/* The exe imports. */
#define MPG123_EXPORT __declspec(dllimport)
#else
/* Nothing on normal/UNIX builds */
#define MPG123_EXPORT
#endif
#endif
#endif

/* This is for Visual Studio, so this header works as distributed in the binary downloads */
#if defined(_MSC_VER) && !defined(MPG123_DEF_SSIZE_T)
#define MPG123_DEF_SSIZE_T
#include <stddef.h>
typedef ptrdiff_t ssize_t;
#endif

#ifndef MPG123_NO_CONFIGURE /* Enable use of this file without configure. */
#include <stdlib.h>
#include <sys/types.h>

/* Simplified large file handling.
	I used to have a check here that prevents building for a library with conflicting large file setup
	(application that uses 32 bit offsets with library that uses 64 bits).
	While that was perfectly fine in an environment where there is one incarnation of the library,
	it hurt GNU/Linux and Solaris systems with multilib where the distribution fails to provide the
	correct header matching the 32 bit library (where large files need explicit support) or
	the 64 bit library (where there is no distinction).

	New approach: When the app defines _FILE_OFFSET_BITS, it wants non-default large file support,
	and thus functions with added suffix (mpg123_open_64).
	Any mismatch will be caught at link time because of the _FILE_OFFSET_BITS setting used when
	building libmpg123. Plus, there's dual mode large file support in mpg123 since 1.12 now.
	Link failure is not the expected outcome of any half-sane usage anymore.

	More complication: What about client code defining _LARGEFILE64_SOURCE? It might want direct access to the _64 functions, along with the ones without suffix. Well, that's possible now via defining MPG123_NO_LARGENAME and MPG123_LARGESUFFIX, respectively, for disabling or enforcing the suffix names.
*/

/*
	Now, the renaming of large file aware functions.
	By default, it appends underscore _FILE_OFFSET_BITS (so, mpg123_seek_64 for mpg123_seek), if _FILE_OFFSET_BITS is defined. You can force a different suffix via MPG123_LARGESUFFIX (that must include the underscore), or you can just disable the whole mess by defining MPG123_NO_LARGENAME.
*/
#if (!defined MPG123_NO_LARGENAME) && ((defined _FILE_OFFSET_BITS) || (defined MPG123_LARGESUFFIX))

/* Need some trickery to concatenate the value(s) of the given macro(s). */
#define MPG123_MACROCAT_REALLY(a, b) a ## b
#define MPG123_MACROCAT(a, b) MPG123_MACROCAT_REALLY(a, b)
#ifndef MPG123_LARGESUFFIX
#define MPG123_LARGESUFFIX MPG123_MACROCAT(_, _FILE_OFFSET_BITS)
#endif
#define MPG123_LARGENAME(func) MPG123_MACROCAT(func, MPG123_LARGESUFFIX)

#define mpg123_open_fixed   MPG123_LARGENAME(mpg123_open_fixed)
#define mpg123_open         MPG123_LARGENAME(mpg123_open)
#define mpg123_open_fd      MPG123_LARGENAME(mpg123_open_fd)
#define mpg123_open_handle  MPG123_LARGENAME(mpg123_open_handle)
#define mpg123_framebyframe_decode MPG123_LARGENAME(mpg123_framebyframe_decode)
#define mpg123_decode_frame MPG123_LARGENAME(mpg123_decode_frame)
#define mpg123_tell         MPG123_LARGENAME(mpg123_tell)
#define mpg123_tellframe    MPG123_LARGENAME(mpg123_tellframe)
#define mpg123_tell_stream  MPG123_LARGENAME(mpg123_tell_stream)
#define mpg123_seek         MPG123_LARGENAME(mpg123_seek)
#define mpg123_feedseek     MPG123_LARGENAME(mpg123_feedseek)
#define mpg123_seek_frame   MPG123_LARGENAME(mpg123_seek_frame)
#define mpg123_timeframe    MPG123_LARGENAME(mpg123_timeframe)
#define mpg123_index        MPG123_LARGENAME(mpg123_index)
#define mpg123_set_index    MPG123_LARGENAME(mpg123_set_index)
#define mpg123_position     MPG123_LARGENAME(mpg123_position)
#define mpg123_length       MPG123_LARGENAME(mpg123_length)
#define mpg123_framelength  MPG123_LARGENAME(mpg123_framelength)
#define mpg123_set_filesize MPG123_LARGENAME(mpg123_set_filesize)
#define mpg123_replace_reader MPG123_LARGENAME(mpg123_replace_reader)
#define mpg123_replace_reader_handle MPG123_LARGENAME(mpg123_replace_reader_handle)
#define mpg123_framepos MPG123_LARGENAME(mpg123_framepos)

#endif /* largefile hackery */

#endif /* MPG123_NO_CONFIGURE */

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup mpg123_init mpg123 library and handle setup
 *
 * Functions to initialise and shutdown the mpg123 library and handles.
 * The parameters of handles have workable defaults, you only have to tune them when you want to tune something;-)
 * Tip: Use a RVA setting...
 *
 * @{
 */

/** Opaque structure for the libmpg123 decoder handle. */
struct mpg123_handle_struct;

/** Opaque structure for the libmpg123 decoder handle.
 *  Most functions take a pointer to a mpg123_handle as first argument and operate on its data in an object-oriented manner.
 */
typedef struct mpg123_handle_struct mpg123_handle;

/** Function to initialise the mpg123 library. 
 * This should be called once in a non-parallel context. It is not explicitly
 * thread-safe, but repeated/concurrent calls still _should_ be safe as static
 * tables are filled with the same values anyway.
 *
 *	\return MPG123_OK if successful, otherwise an error number.
 */
MPG123_EXPORT int mpg123_init(void);

/** Superfluous Function to close down the mpg123 library.
 * This was created with the thought that there sometime will be cleanup code
 * to be run after library use. This never materialized. You can forget about
 * this function and it is only here for old programs that do call it.
 */
MPG123_EXPORT void mpg123_exit(void);

/** Create a handle with optional choice of decoder (named by a string, see mpg123_decoders() or mpg123_supported_decoders()).
 *  and optional retrieval of an error code to feed to mpg123_plain_strerror().
 *  Optional means: Any of or both the parameters may be NULL.
 *
 *  \param decoder optional choice of decoder variant (NULL for default)
 *  \param error optional address to store error codes
 *  \return Non-NULL pointer to fresh handle when successful.
 */
MPG123_EXPORT mpg123_handle *mpg123_new(const char* decoder, int *error);

/** Delete handle, mh is either a valid mpg123 handle or NULL.
 *  \param mh handle
 */
MPG123_EXPORT void mpg123_delete(mpg123_handle *mh);

/** Free plain memory allocated within libmpg123.
 *  This is for library users that are not sure to use the same underlying
 *  memory allocator as libmpg123. It is just a wrapper over free() in
 *  the underlying C library.
 */
MPG123_EXPORT void mpg123_free(void *ptr);

/** Enumeration of the parameters types that it is possible to set/get. */
enum mpg123_parms
{
	MPG123_VERBOSE = 0,        /**< set verbosity value for enabling messages to stderr, >= 0 makes sense (integer) */
	MPG123_FLAGS,          /**< set all flags, p.ex val = MPG123_GAPLESS|MPG123_MONO_MIX (integer) */
	MPG123_ADD_FLAGS,      /**< add some flags (integer) */
	MPG123_FORCE_RATE,     /**< when value > 0, force output rate to that value (integer) */
	MPG123_DOWN_SAMPLE,    /**< 0=native rate, 1=half rate, 2=quarter rate (integer) */
	MPG123_RVA,            /**< one of the RVA choices above (integer) */
	MPG123_DOWNSPEED,      /**< play a frame N times (integer) */
	MPG123_UPSPEED,        /**< play every Nth frame (integer) */
	MPG123_START_FRAME,    /**< start with this frame (skip frames before that, integer) */ 
	MPG123_DECODE_FRAMES,  /**< decode only this number of frames (integer) */
	MPG123_ICY_INTERVAL,   /**< Stream contains ICY metadata with this interval (integer).
	                            Make sure to set this _before_ opening a stream.*/
	MPG123_OUTSCALE,       /**< the scale for output samples (amplitude - integer or float according to mpg123 output format, normally integer) */
	MPG123_TIMEOUT,        /**< timeout for reading from a stream (not supported on win32, integer) */
	MPG123_REMOVE_FLAGS,   /**< remove some flags (inverse of MPG123_ADD_FLAGS, integer) */
	MPG123_RESYNC_LIMIT,   /**< Try resync on frame parsing for that many bytes or until end of stream (<0 ... integer). This can enlarge the limit for skipping junk on beginning, too (but not reduce it).  */
	MPG123_INDEX_SIZE      /**< Set the frame index size (if supported). Values <0 mean that the index is allowed to grow dynamically in these steps (in positive direction, of course) -- Use this when you really want a full index with every individual frame. */
	,MPG123_PREFRAMES /**< Decode/ignore that many frames in advance for layer 3. This is needed to fill bit reservoir after seeking, for example (but also at least one frame in advance is needed to have all "normal" data for layer 3). Give a positive integer value, please.*/
	,MPG123_FEEDPOOL  /**< For feeder mode, keep that many buffers in a pool to avoid frequent malloc/free. The pool is allocated on mpg123_open_feed(). If you change this parameter afterwards, you can trigger growth and shrinkage during decoding. The default value could change any time. If you care about this, then set it. (integer) */
	,MPG123_FEEDBUFFER /**< Minimal size of one internal feeder buffer, again, the default value is subject to change. (integer) */
	,MPG123_FREEFORMAT_SIZE /**< Tell the parser a free-format frame size to
	 * avoid read-ahead to get it. A value of -1 (default) means that the parser
	 * will determine it. The parameter value is applied during decoder setup
	 * for a freshly opened stream only.
	 */
};

/** Flag bits for MPG123_FLAGS, use the usual binary or to combine. */
enum mpg123_param_flags
{
	 MPG123_FORCE_MONO   = 0x7  /**<     0111 Force some mono mode: This is a test bitmask for seeing if any mono forcing is active. */
	,MPG123_MONO_LEFT    = 0x1  /**<     0001 Force playback of left channel only.  */
	,MPG123_MONO_RIGHT   = 0x2  /**<     0010 Force playback of right channel only. */
	,MPG123_MONO_MIX     = 0x4  /**<     0100 Force playback of mixed mono.         */
	,MPG123_FORCE_STEREO = 0x8  /**<     1000 Force stereo output.                  */
	,MPG123_FORCE_8BIT   = 0x10 /**< 00010000 Force 8bit formats.                   */
	,MPG123_QUIET        = 0x20 /**< 00100000 Suppress any printouts (overrules verbose).                    */
	,MPG123_GAPLESS      = 0x40 /**< 01000000 Enable gapless decoding (default on if libmpg123 has support). */
	,MPG123_NO_RESYNC    = 0x80 /**< 10000000 Disable resync stream after error.                             */
	,MPG123_SEEKBUFFER   = 0x100 /**< 000100000000 Enable small buffer on non-seekable streams to allow some peek-ahead (for better MPEG sync). */
	,MPG123_FUZZY        = 0x200 /**< 001000000000 Enable fuzzy seeks (guessing byte offsets or using approximate seek points from Xing TOC) */
	,MPG123_FORCE_FLOAT  = 0x400 /**< 010000000000 Force floating point output (32 or 64 bits depends on mpg123 internal precision). */
	,MPG123_PLAIN_ID3TEXT = 0x800 /**< 100000000000 Do not translate ID3 text data to UTF-8. ID3 strings will contain the raw text data, with the first byte containing the ID3 encoding code. */
	,MPG123_IGNORE_STREAMLENGTH = 0x1000 /**< 1000000000000 Ignore any stream length information contained in the stream, which can be contained in a 'TLEN' frame of an ID3v2 tag or a Xing tag */
	,MPG123_SKIP_ID3V2 = 0x2000 /**< 10 0000 0000 0000 Do not parse ID3v2 tags, just skip them. */
	,MPG123_IGNORE_INFOFRAME = 0x4000 /**< 100 0000 0000 0000 Do not parse the LAME/Xing info frame, treat it as normal MPEG data. */
	,MPG123_AUTO_RESAMPLE = 0x8000 /**< 1000 0000 0000 0000 Allow automatic internal resampling of any kind (default on if supported). Especially when going lowlevel with replacing output buffer, you might want to unset this flag. Setting MPG123_DOWNSAMPLE or MPG123_FORCE_RATE will override this. */
	,MPG123_PICTURE = 0x10000 /**< 17th bit: Enable storage of pictures from tags (ID3v2 APIC). */
	,MPG123_NO_PEEK_END    = 0x20000 /**< 18th bit: Do not seek to the end of
	 *  the stream in order to probe
	 *  the stream length and search for the id3v1 field. This also means
	 *  the file size is unknown unless set using mpg123_set_filesize() and
	 *  the stream is assumed as non-seekable unless overridden.
	 */
	,MPG123_FORCE_SEEKABLE = 0x40000 /**< 19th bit: Force the stream to be seekable. */
	,MPG123_STORE_RAW_ID3  = 0x80000 /**< store raw ID3 data (even if skipping) */
	,MPG123_FORCE_ENDIAN   = 0x100000 /**< Enforce endianess of output samples.
	 *  This is not reflected in the format codes. If this flag is set along with
	 *  MPG123_BIG_ENDIAN, MPG123_ENC_SIGNED16 means s16be, without
	 *  MPG123_BIG_ENDIAN, it means s16le. Normal operation without
	 *  MPG123_FORCE_ENDIAN produces output in native byte order.
	 */
	,MPG123_BIG_ENDIAN     = 0x200000 /**< Choose big endian instead of little. */
	,MPG123_NO_READAHEAD   = 0x400000 /**< Disable read-ahead in parser. If
	 * you know you provide full frames to the feeder API, this enables
	 * decoder output from the first one on, instead of having to wait for
	 * the next frame to confirm that the stream is healthy. It also disables
	 * free format support unless you provide a frame size using
	 * MPG123_FREEFORMAT_SIZE.
	 */
	,MPG123_FLOAT_FALLBACK = 0x800000 /**< Consider floating point output encoding only after
	 * trying other (possibly downsampled) rates and encodings first. This is to
	 * support efficient playback where floating point output is only configured for
	 * an external resampler, bypassing that resampler when the desired rate can
	 * be produced directly. This is enabled by default to be closer to older versions
	 * of libmpg123 which did not enable float automatically at all. If disabled,
	 * float is considered after the 16 bit default and higher-bit integer encodings
	 * for any rate. */
	,MPG123_NO_FRANKENSTEIN = 0x1000000 /**< Disable support for Frankenstein streams
	 * (different MPEG streams stiched together). Do not accept serious change of MPEG
	 * header inside a single stream. With this flag, the audio output format cannot
	 * change during decoding unless you open a new stream. This also stops decoding
	 * after an announced end of stream (Info header contained a number of frames
	 * and this number has been reached). This makes your MP3 files behave more like
	 * ordinary media files with defined structure, rather than stream dumps with
	 * some sugar. */
};

/** choices for MPG123_RVA */
enum mpg123_param_rva
{
	 MPG123_RVA_OFF   = 0 /**< RVA disabled (default).   */
	,MPG123_RVA_MIX   = 1 /**< Use mix/track/radio gain. */
	,MPG123_RVA_ALBUM = 2 /**< Use album/audiophile gain */
	,MPG123_RVA_MAX   = MPG123_RVA_ALBUM /**< The maximum RVA code, may increase in future. */
};

/** Set a specific parameter, for a specific mpg123_handle, using a parameter 
 *  type key chosen from the mpg123_parms enumeration, to the specified value.
 *  \param mh handle
 *  \param type parameter choice
 *  \param value integer value
 *  \param fvalue floating point value
 *  \return MPG123_OK on success
 */
MPG123_EXPORT int mpg123_param( mpg123_handle *mh
,	enum mpg123_parms type, long value, double fvalue );

/** Get a specific parameter, for a specific mpg123_handle. 
 *  See the mpg123_parms enumeration for a list of available parameters.
 *  \param mh handle
 *  \param type parameter choice
 *  \param value integer value return address
 *  \param fvalue floating point value return address
 *  \return MPG123_OK on success
 */
MPG123_EXPORT int mpg123_getparam( mpg123_handle *mh
,	enum mpg123_parms type, long *value, double *fvalue );

/** Feature set available for query with mpg123_feature. */
enum mpg123_feature_set
{
	 MPG123_FEATURE_ABI_UTF8OPEN = 0     /**< mpg123 expects path names to be given in UTF-8 encoding instead of plain native. */
	,MPG123_FEATURE_OUTPUT_8BIT          /**< 8bit output   */
	,MPG123_FEATURE_OUTPUT_16BIT         /**< 16bit output  */
	,MPG123_FEATURE_OUTPUT_32BIT         /**< 32bit output  */
	,MPG123_FEATURE_INDEX                /**< support for building a frame index for accurate seeking */
	,MPG123_FEATURE_PARSE_ID3V2          /**< id3v2 parsing */
	,MPG123_FEATURE_DECODE_LAYER1        /**< mpeg layer-1 decoder enabled */
	,MPG123_FEATURE_DECODE_LAYER2        /**< mpeg layer-2 decoder enabled */
	,MPG123_FEATURE_DECODE_LAYER3        /**< mpeg layer-3 decoder enabled */
	,MPG123_FEATURE_DECODE_ACCURATE      /**< accurate decoder rounding    */
	,MPG123_FEATURE_DECODE_DOWNSAMPLE    /**< downsample (sample omit)     */
	,MPG123_FEATURE_DECODE_NTOM          /**< flexible rate decoding       */
	,MPG123_FEATURE_PARSE_ICY            /**< ICY support                  */
	,MPG123_FEATURE_TIMEOUT_READ         /**< Reader with timeout (network). */
	,MPG123_FEATURE_EQUALIZER            /**< tunable equalizer */
	,MPG123_FEATURE_MOREINFO             /**< more info extraction (for frame analyzer) */
	,MPG123_FEATURE_OUTPUT_FLOAT32      /**< 32 bit float output */
	,MPG123_FEATURE_OUTPUT_FLOAT64      /**< 64 bit float output (usually never) */
};

/** Query libmpg123 features.
 *  \param key feature selection
 *  \return 1 for success, 0 for unimplemented functions
 */
MPG123_EXPORT int mpg123_feature(const enum mpg123_feature_set key);

/** Query libmpg123 features with better ABI compatibility
 *
 *  This is the same as mpg123_feature(), but this time not using
 *  the enum as argument. Compilers don't have to agree on the size of
 *  enums and hence they are not safe in public API.
 *
 *  \param key feature selection
 *  \return 1 for success, 0 for unimplemented functions
 */
MPG123_EXPORT int mpg123_feature2(int key);

/* @} */


/** \defgroup mpg123_error mpg123 error handling
 *
 * Functions to get text version of the error numbers and an enumeration
 * of the error codes returned by libmpg123.
 *
 * Most functions operating on a mpg123_handle simply return MPG123_OK (0)
 * on success and MPG123_ERR (-1) on failure, setting the internal error
 * variable of the handle to the specific error code. If there was not a valid
 * (non-NULL) handle provided to a function operating on one, MPG123_BAD_HANDLE
 * may be returned if this can not be confused with a valid positive return
 * value.
 * Meaning: A function expected to return positive integers on success will
 * always indicate error or a special condition by returning a negative one.
 *
 * Decoding/seek functions may also return message codes MPG123_DONE,
 * MPG123_NEW_FORMAT and MPG123_NEED_MORE (all negative, see below on how to
 * react). Note that calls to those can be nested, so generally watch out
 * for these codes after initial handle setup.
 * Especially any function that needs information about the current stream
 * to work will try to at least parse the beginning if that did not happen
 * yet.
 *
 * On a function that is supposed to return MPG123_OK on success and
 * MPG123_ERR on failure, make sure you check for != MPG123_OK, not
 * == MPG123_ERR, as the error code could get more specific in future,
 * or there is just a special message from a decoding routine as indicated
 * above.
 *
 * @{
 */

/** Enumeration of the message and error codes and returned by libmpg123 functions. */
enum mpg123_errors
{
	MPG123_DONE=-12,	/**< Message: Track ended. Stop decoding. */
	MPG123_NEW_FORMAT=-11,	/**< Message: Output format will be different on next call. Note that some libmpg123 versions between 1.4.3 and 1.8.0 insist on you calling mpg123_getformat() after getting this message code. Newer verisons behave like advertised: You have the chance to call mpg123_getformat(), but you can also just continue decoding and get your data. */
	MPG123_NEED_MORE=-10,	/**< Message: For feed reader: "Feed me more!" (call mpg123_feed() or mpg123_decode() with some new input data). */
	MPG123_ERR=-1,			/**< Generic Error */
	MPG123_OK=0, 			/**< Success */
	MPG123_BAD_OUTFORMAT, 	/**< Unable to set up output format! */
	MPG123_BAD_CHANNEL,		/**< Invalid channel number specified. */
	MPG123_BAD_RATE,		/**< Invalid sample rate specified.  */
	MPG123_ERR_16TO8TABLE,	/**< Unable to allocate memory for 16 to 8 converter table! */
	MPG123_BAD_PARAM,		/**< Bad parameter id! */
	MPG123_BAD_BUFFER,		/**< Bad buffer given -- invalid pointer or too small size. */
	MPG123_OUT_OF_MEM,		/**< Out of memory -- some malloc() failed. */
	MPG123_NOT_INITIALIZED,	/**< You didn't initialize the library! */
	MPG123_BAD_DECODER,		/**< Invalid decoder choice. */
	MPG123_BAD_HANDLE,		/**< Invalid mpg123 handle. */
	MPG123_NO_BUFFERS,		/**< Unable to initialize frame buffers (out of memory?). */
	MPG123_BAD_RVA,			/**< Invalid RVA mode. */
	MPG123_NO_GAPLESS,		/**< This build doesn't support gapless decoding. */
	MPG123_NO_SPACE,		/**< Not enough buffer space. */
	MPG123_BAD_TYPES,		/**< Incompatible numeric data types. */
	MPG123_BAD_BAND,		/**< Bad equalizer band. */
	MPG123_ERR_NULL,		/**< Null pointer given where valid storage address needed. */
	MPG123_ERR_READER,		/**< Error reading the stream. */
	MPG123_NO_SEEK_FROM_END,/**< Cannot seek from end (end is not known). */
	MPG123_BAD_WHENCE,		/**< Invalid 'whence' for seek function.*/
	MPG123_NO_TIMEOUT,		/**< Build does not support stream timeouts. */
	MPG123_BAD_FILE,		/**< File access error. */
	MPG123_NO_SEEK,			/**< Seek not supported by stream. */
	MPG123_NO_READER,		/**< No stream opened. */
	MPG123_BAD_PARS,		/**< Bad parameter handle. */
	MPG123_BAD_INDEX_PAR,	/**< Bad parameters to mpg123_index() and mpg123_set_index() */
	MPG123_OUT_OF_SYNC,	/**< Lost track in bytestream and did not try to resync. */
	MPG123_RESYNC_FAIL,	/**< Resync failed to find valid MPEG data. */
	MPG123_NO_8BIT,	/**< No 8bit encoding possible. */
	MPG123_BAD_ALIGN,	/**< Stack aligmnent error */
	MPG123_NULL_BUFFER,	/**< NULL input buffer with non-zero size... */
	MPG123_NO_RELSEEK,	/**< Relative seek not possible (screwed up file offset) */
	MPG123_NULL_POINTER, /**< You gave a null pointer somewhere where you shouldn't have. */
	MPG123_BAD_KEY,	/**< Bad key value given. */
	MPG123_NO_INDEX,	/**< No frame index in this build. */
	MPG123_INDEX_FAIL,	/**< Something with frame index went wrong. */
	MPG123_BAD_DECODER_SETUP,	/**< Something prevents a proper decoder setup */
	MPG123_MISSING_FEATURE  /**< This feature has not been built into libmpg123. */
	,MPG123_BAD_VALUE /**< A bad value has been given, somewhere. */
	,MPG123_LSEEK_FAILED /**< Low-level seek failed. */
	,MPG123_BAD_CUSTOM_IO /**< Custom I/O not prepared. */
	,MPG123_LFS_OVERFLOW /**< Offset value overflow during translation of large file API calls -- your client program cannot handle that large file. */
	,MPG123_INT_OVERFLOW /**< Some integer overflow. */
};

/** Look up error strings given integer code.
 *  \param errcode integer error code
 *  \return string describing what that error error code means
 */
MPG123_EXPORT const char* mpg123_plain_strerror(int errcode);

/** Give string describing what error has occured in the context of handle mh.
 *  When a function operating on an mpg123 handle returns MPG123_ERR, you should check for the actual reason via
 *  char *errmsg = mpg123_strerror(mh)
 *  This function will catch mh == NULL and return the message for MPG123_BAD_HANDLE.
 *  \param mh handle
 *  \return error message
 */
MPG123_EXPORT const char* mpg123_strerror(mpg123_handle *mh);

/** Return the plain errcode intead of a string.
 *  \param mh handle
 *  \return error code recorded in handle or MPG123_BAD_HANDLE
 */
MPG123_EXPORT int mpg123_errcode(mpg123_handle *mh);

/*@}*/


/** \defgroup mpg123_decoder mpg123 decoder selection
 *
 * Functions to list and select the available decoders.
 * Perhaps the most prominent feature of mpg123: You have several (optimized) decoders to choose from (on x86 and PPC (MacOS) systems, that is).
 *
 * @{
 */

/** Get available decoder list.
 *  \return NULL-terminated array of generally available decoder names (plain 8bit ASCII)
 */
MPG123_EXPORT const char **mpg123_decoders(void);

/** Get supported decoder list.
 *  \return NULL-terminated array of the decoders supported by the CPU (plain 8bit ASCII)
 */
MPG123_EXPORT const char **mpg123_supported_decoders(void);

/** Set the active decoder.
 *  \param mh handle
 *  \param decoder_name name of decoder
 *  \return MPG123_OK on success
 */
MPG123_EXPORT int mpg123_decoder(mpg123_handle *mh, const char* decoder_name);

/** Get the currently active decoder name.
 *  The active decoder engine can vary depening