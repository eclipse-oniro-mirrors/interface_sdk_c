/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup UDMF
 * @{
 *
 * @brief 统一数据管理框架旨在定义数据跨应用、跨设备以及跨平台过程中的各项标准，
 * 提供统一的OpenHarmony数据语言和标准化的数据接入与读取通路。
 *
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */
/**
 * @file udmf_meta.h
 *
 * @brief 声明统一类型数据信息。
 *
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */

#ifndef UDMF_META_H
#define UDMF_META_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_ENTITY "general.entity"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OBJECT "general.object"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_COMPOSITE_OBJECT "general.composite-object"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_TEXT "general.text"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PLAIN_TEXT "general.plain-text"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_HTML "general.html"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_HYPERLINK "general.hyperlink"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_XML "general.xml"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_SOURCE_CODE "general.source-code"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_SCRIPT "general.script"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_SHELL_SCRIPT "general.shell-script"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_CSH_SCRIPT "general.csh-script"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PERL_SCRIPT "general.perl-script"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PHP_SCRIPT "general.php-script"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PYTHON_SCRIPT "general.python-script"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_RUBY_SCRIPT "general.ruby-script"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_TYPE_SCRIPT "general.type-script"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_JAVA_SCRIPT "general.java-script"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_C_HEADER "general.c-header"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_C_SOURCE "general.c-source"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_C_PLUS_PLUS_HEADER "general.c-plus-plus-header"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_C_PLUS_PLUS_SOURCE "general.c-plus-plus-source"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_JAVA_SOURCE "general.java-source"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_EBOOK "general.ebook"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_EPUB "general.epub"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_AZW "com.amazon.azw"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_AZW3 "com.amazon.azw3"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_KFX "com.amazon.kfx"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_MOBI "com.amazon.mobi"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_MEDIA "general.media"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_IMAGE "general.image"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_JPEG "general.jpeg"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PNG "general.png"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_RAW_IMAGE "general.raw-image"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_TIFF "general.tiff"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_BMP "com.microsoft.bmp"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_ICO "com.microsoft.ico"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PHOTOSHOP_IMAGE "com.adobe.photoshop-image"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_AI_IMAGE "com.adobe.illustrator.ai-image"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_WORD_DOC "com.microsoft.word.doc"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_EXCEL "com.microsoft.excel.xls"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PPT "com.microsoft.powerpoint.ppt"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PDF "com.adobe.pdf"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT "com.adobe.postscript"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_ENCAPSULATED_POSTSCRIPT "com.adobe.encapsulated-postscript"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_VIDEO "general.video"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_AVI "general.avi"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_MPEG "general.mpeg"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_MPEG4 "general.mpeg-4"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_VIDEO_3GPP "general.3gpp"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_VIDEO_3GPP2 "general.3gpp2"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WM "com.microsoft.windows-media-wm"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMV "com.microsoft.windows-media-wmv"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMP "com.microsoft.windows-media-wmp"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_AUDIO "general.audio"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_AAC "general.aac"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_AIFF "general.aiff"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_ALAC "general.alac"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_FLAC "general.flac"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_MP3 "general.mp3"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OGG "general.ogg"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PCM "general.pcm"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMA "com.microsoft.windows-media-wma"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_WAVEFORM_AUDIO "com.microsoft.waveform-audio"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMX "com.microsoft.windows-media-wmx"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WVX "com.microsoft.windows-media-wvx"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WAX "com.microsoft.windows-media-wax"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_GENERAL_FILE "general.file"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_DIRECTORY "general.directory"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_FOLDER "general.folder"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_SYMLINK "general.symlink"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_ARCHIVE "general.archive"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_BZ2_ARCHIVE "general.bz2-archive"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_DISK_IMAGE "general.disk-image"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_TAR_ARCHIVE "general.tar-archive"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_ZIP_ARCHIVE "general.zip-archive"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_JAVA_ARCHIVE "com.sun.java-archive"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_GNU_TAR_ARCHIVE "org.gnu.gnu-tar-archive"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_GNU_ZIP_ARCHIVE "org.gnu.gnu-zip-archive"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_GNU_ZIP_TAR_ARCHIVE "org.gnu.gnu-zip-tar-archive"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_CALENDAR "general.calendar"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_CONTACT "general.contact"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_DATABASE "general.database"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_MESSAGE "general.message"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_VCARD "general.vcard"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_NAVIGATION "general.navigation"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_LOCATION "general.location"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_FORM "openharmony.form"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_APP_ITEM "openharmony.app-item"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_PIXEL_MAP "openharmony.pixel-map"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_ATOMIC_SERVICE "openharmony.atomic-service"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_PACKAGE "openharmony.package"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HAP "openharmony.hap"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_SMIL "com.real.smil"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_MARKDOWN "general.markdown"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_FAX "general.fax"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_JFX_FAX "com.j2.jfx-fax"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_EFX_FAX "com.js.efx-fax"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_XBITMAP_IMAGE "general.xbitmap-image"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_TGA_IMAGE "com.truevision.tga-image"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_SGI_IMAGE "com.sgi.sgi-image"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENEXR_IMAGE "com.ilm.openexr-image"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_FLASHPIX_IMAGE "com.kodak.flashpix.image"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_REALMEDIA "com.real.realmedia"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_AU_AUDIO "general.au-audio"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_AIFC_AUDIO "general.aifc-audio"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_SD2_AUDIO "com.digidesign.sd2-audio"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_REALAUDIO "com.real.realaudio"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENXML "org.openxmlformats.openxml"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_WORDPROCESSINGML_DOCUMENT "org.openxmlformats.wordprocessingml.document"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_SPREADSHEETML_SHEET "org.openxmlformats.spreadsheetml.sheet"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PRESENTATIONML_PRESENTATION "org.openxmlformats.presentationml.presentation"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT "org.oasis.opendocument"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_TEXT "org.oasis.opendocument.text"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_SPREADSHEET "org.oasis.opendocument.spreadsheet"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_PRESENTATION "org.oasis.opendocument.presentation"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_GRAPHICS "org.oasis.opendocument.graphics"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_FORMULA "org.oasis.opendocument.formula"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_STUFFIT_ARCHIVE "com.allume.stuffit-archive"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_VCS "general.vcs"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_ICS "general.ics"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_EXECUTABLE "general.executable"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_PORTABLE_EXECUTABLE "com.microsoft.portable-executable"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_SUN_JAVA_CLASS "com.sun.java-class"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_FONT "general.font"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_TRUETYPE_FONT "general.truetype-font"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_TRUETYPE_COLLECTION_FONT "general.truetype-collection-font"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENTYPE_FONT "general.opentype-font"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_FONT "com.adobe.postscript-font"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_PFB_FONT "com.adobe.postscript-pfb-font"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_PFA_FONT "com.adobe.postscript-pfa-font"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HDOC "openharmony.hdoc"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HINOTE "openharmony.hinote"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_STYLED_STRING "openharmony.styled-string"

/**
 * @brief 所有表示物理存储类型的基类型，用于描述类型的物理属性，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_WANT "openharmony.want"

/**
 * @brief 文件地址类型，归属类型为TEXT。
 *
 * @since 13
 */
#define UDMF_META_GENERAL_FILE_URI "general.file-uri"

/**
 * @brief 内容卡片类型，归属类型为OBJECT。
 *
 * @since 14
 */
#define UDMF_METE_GENERAL_CONTENT_FORM "general.content-form"

#ifdef __cplusplus
};
#endif

/** @} */
#endif