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
 * @brief 所有表示逻辑内容类型的基类型，用于描述类型的功能性特征，无归属类型。
 *
 * @since 12
 */
#define UDMF_META_OBJECT "general.object"

/**
 * @brief 所有组合内容类型（例如PDF文件类型混合了文本和图片类数据）的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_COMPOSITE_OBJECT "general.composite-object"

/**
 * @brief 所有文本的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_TEXT "general.text"

/**
 * @brief 未指定编码的文本类型，没有标识符，归属类型为TEXT。
 *
 * @since 12
 */
#define UDMF_META_PLAIN_TEXT "general.plain-text"

/**
 * @brief HTML文本类型，归属类型为TEXT。
 *
 * @since 12
 */
#define UDMF_META_HTML "general.html"

/**
 * @brief 超链接类型，归属类型为TEXT。
 *
 * @since 12
 */
#define UDMF_META_HYPERLINK "general.hyperlink"

/**
 * @brief XML文本类型，归属类型为TEXT。
 *
 * @since 12
 */
#define UDMF_META_XML "general.xml"

/**
 * @brief 所有源代码的基类型，归属类型为PLAIN_TEXT。
 *
 * @since 12
 */
#define UDMF_META_SOURCE_CODE "general.source-code"

/**
 * @brief 所有脚本语言源代码的基类型，归属类型为SOURCE_CODE。
 *
 * @since 12
 */
#define UDMF_META_SCRIPT "general.script"

/**
 * @brief Shell脚本类型，归属类型为SCRIPT。
 *
 * @since 12
 */
#define UDMF_META_SHELL_SCRIPT "general.shell-script"

/**
 * @brief C-shell脚本类型，归属类型为SHELL_SCRIPT。
 *
 * @since 12
 */
#define UDMF_META_CSH_SCRIPT "general.csh-script"

/**
 * @brief Perl脚本类型，归属类型为SHELL_SCRIPT。
 *
 * @since 12
 */
#define UDMF_META_PERL_SCRIPT "general.perl-script"

/**
 * @brief PHP脚本类型，归属类型为SHELL_SCRIPT。
 *
 * @since 12
 */
#define UDMF_META_PHP_SCRIPT "general.php-script"

/**
 * @brief Python脚本类型，归属类型为SHELL_SCRIPT。
 *
 * @since 12
 */
#define UDMF_META_PYTHON_SCRIPT "general.python-script"

/**
 * @brief Ruby脚本类型，归属类型为SHELL_SCRIPT。
 *
 * @since 12
 */
#define UDMF_META_RUBY_SCRIPT "general.ruby-script"

/**
 * @brief TypeScript源代码类型，归属类型为SCRIPT。
 *
 * @since 12
 */
#define UDMF_META_TYPE_SCRIPT "general.type-script"

/**
 * @brief JavaScript源代码类型，归属类型为SCRIPT。
 *
 * @since 12
 */
#define UDMF_META_JAVA_SCRIPT "general.java-script"

/**
 * @brief C头文件类型，归属类型为SOURCE_CODE。
 *
 * @since 12
 */
#define UDMF_META_C_HEADER "general.c-header"

/**
 * @brief C源代码类型，归属类型为SOURCE_CODE。
 *
 * @since 12
 */
#define UDMF_META_C_SOURCE "general.c-source"

/**
 * @brief C++头文件类型，归属类型为SOURCE_CODE。
 *
 * @since 12
 */
#define UDMF_META_C_PLUS_PLUS_HEADER "general.c-plus-plus-header"

/**
 * @brief C++源代码类型，归属类型为SOURCE_CODE。
 *
 * @since 12
 */
#define UDMF_META_C_PLUS_PLUS_SOURCE "general.c-plus-plus-source"

/**
 * @brief Java源代码类型，归属类型为SOURCE_CODE。
 *
 * @since 12
 */
#define UDMF_META_JAVA_SOURCE "general.java-source"

/**
 * @brief 所有电子书文件格式的基类型，归属类型为COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_EBOOK "general.ebook"

/**
 * @brief 电子出版物（EPUB）文件格式类型，归属类型为EBOOK。
 *
 * @since 12
 */
#define UDMF_META_EPUB "general.epub"

/**
 * @brief AZW电子书文件格式类型，归属类型为EBOOK。
 *
 * @since 12
 */
#define UDMF_META_AZW "com.amazon.azw"

/**
 * @brief AZW3电子书文件格式类型，归属类型为EBOOK。
 *
 * @since 12
 */
#define UDMF_META_AZW3 "com.amazon.azw3"

/**
 * @brief KFX电子书文件格式类型，归属类型为EBOOK。
 *
 * @since 12
 */
#define UDMF_META_KFX "com.amazon.kfx"

/**
 * @brief MOBI电子书文件格式类型，归属类型为EBOOK。
 *
 * @since 12
 */
#define UDMF_META_MOBI "com.amazon.mobi"

/**
 * @brief 所有媒体的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_MEDIA "general.media"

/**
 * @brief 所有图片的基类型，归属类型为MEDIA。
 *
 * @since 12
 */
#define UDMF_META_IMAGE "general.image"

/**
 * @brief JPEG图片类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_JPEG "general.jpeg"

/**
 * @brief PNG图片类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_PNG "general.png"

/**
 * @brief 所有原始图像格式的基类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_RAW_IMAGE "general.raw-image"

/**
 * @brief TIFF图片类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_TIFF "general.tiff"

/**
 * @brief WINDOWS位图图像类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_BMP "com.microsoft.bmp"

/**
 * @brief WINDOWS图标图像类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_ICO "com.microsoft.ico"

/**
 * @brief Adobe Photoshop图片类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_PHOTOSHOP_IMAGE "com.adobe.photoshop-image"

/**
 * @brief Adobe Illustrator图片类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_AI_IMAGE "com.adobe.illustrator.ai-image"

/**
 * @brief Microsoft Word数据类型，归属类型为COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_WORD_DOC "com.microsoft.word.doc"

/**
 * @brief Microsoft Excel数据类型，归属类型为COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_EXCEL "com.microsoft.excel.xls"

/**
 * @brief Microsoft PowerPoint演示文稿类型，归属类型为
 *
 * @since 12
 */
#define UDMF_META_PPT "com.microsoft.powerpoint.ppt"

/**
 * @brief PDF数据类型，归属类型为COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_PDF "com.adobe.pdf"

/**
 * @brief PostScript数据类型，归属类型为COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT "com.adobe.postscript"

/**
 * @brief Encapsulated PostScript类型，归属类型为POSTSCRIPT。
 *
 * @since 12
 */
#define UDMF_META_ENCAPSULATED_POSTSCRIPT "com.adobe.encapsulated-postscript"

/**
 * @brief 所有视频的基类型，归属类型为MEDIA。
 *
 * @since 12
 */
#define UDMF_META_VIDEO "general.video"

/**
 * @brief AVI视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_AVI "general.avi"

/**
 * @brief MPEG-1或MPEG-2视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_MPEG "general.mpeg"

/**
 * @brief MPEG-4视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_MPEG4 "general.mpeg-4"

/**
 * @brief 3GPP视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_VIDEO_3GPP "general.3gpp"

/**
 * @brief 3GPP2视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_VIDEO_3GPP2 "general.3gpp2"

/**
 * @brief WINDOWS WM视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WM "com.microsoft.windows-media-wm"

/**
 * @brief WINDOWS WMV视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMV "com.microsoft.windows-media-wmv"

/**
 * @brief WINDOWS WMP视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMP "com.microsoft.windows-media-wmp"

/**
 * @brief 所有音频的基类型，归属类型为MEDIA。
 *
 * @since 12
 */
#define UDMF_META_AUDIO "general.audio"

/**
 * @brief AAC音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_AAC "general.aac"

/**
 * @brief AIFF音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_AIFF "general.aiff"

/**
 * @brief ALAC音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_ALAC "general.alac"

/**
 * @brief FLAC音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_FLAC "general.flac"

/**
 * @brief MP3音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_MP3 "general.mp3"

/**
 * @brief OGG音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_OGG "general.ogg"

/**
 * @brief PCM音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_PCM "general.pcm"

/**
 * @brief WINDOWS WMA音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMA "com.microsoft.windows-media-wma"

/**
 * @brief WINDOWS波形音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_WAVEFORM_AUDIO "com.microsoft.waveform-audio"

/**
 * @brief WINDOWS WMX视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WMX "com.microsoft.windows-media-wmx"

/**
 * @brief WINDOWS WVX视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WVX "com.microsoft.windows-media-wvx"

/**
 * @brief WINDOWS WAX音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_WINDOWS_MEDIA_WAX "com.microsoft.windows-media-wax"

/**
 * @brief 所有文件的基类型，归属类型为ENTITY。
 *
 * @since 12
 */
#define UDMF_META_GENERAL_FILE "general.file"

/**
 * @brief 所有目录的基类型，归属类型为ENTITY。
 *
 * @since 12
 */
#define UDMF_META_DIRECTORY "general.directory"

/**
 * @brief 所有文件夹的基类型，归属类型为DIRECTORY。
 *
 * @since 12
 */
#define UDMF_META_FOLDER "general.folder"

/**
 * @brief 所有符号链接的基类型，归属类型为ENTITY。
 *
 * @since 12
 */
#define UDMF_META_SYMLINK "general.symlink"

/**
 * @brief 所有文件和目录存档文件的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_ARCHIVE "general.archive"

/**
 * @brief BZ2存档文件类型，归属类型为ARCHIVE。
 *
 * @since 12
 */
#define UDMF_META_BZ2_ARCHIVE "general.bz2-archive"

/**
 * @brief 所有可作为卷装载项的文件类型的基类型，归属类型为ARCHIVE。
 *
 * @since 12
 */
#define UDMF_META_DISK_IMAGE "general.disk-image"

/**
 * @brief TAR存档文件类型，归属类型为ARCHIVE。
 *
 * @since 12
 */
#define UDMF_META_TAR_ARCHIVE "general.tar-archive"

/**
 * @brief ZIP存档文件类型，归属类型为ARCHIVE。
 *
 * @since 12
 */
#define UDMF_META_ZIP_ARCHIVE "general.zip-archive"

/**
 * @brief JAVA存档文件类型，归属类型为ARCHIVE和EXECUTABLE。
 *
 * @since 12
 */
#define UDMF_META_JAVA_ARCHIVE "com.sun.java-archive"

/**
 * @brief GNU存档文件类型，归属类型为ARCHIVE。
 *
 * @since 12
 */
#define UDMF_META_GNU_TAR_ARCHIVE "org.gnu.gnu-tar-archive"

/**
 * @brief GZIP存档文件类型，归属类型为ARCHIVE。
 *
 * @since 12
 */
#define UDMF_META_GNU_ZIP_ARCHIVE "org.gnu.gnu-zip-archive"

/**
 * @brief GZIP TAR存档文件类型，归属类型为ARCHIVE。
 *
 * @since 12
 */
#define UDMF_META_GNU_ZIP_TAR_ARCHIVE "org.gnu.gnu-zip-tar-archive"

/**
 * @brief 所有日程类数据的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_CALENDAR "general.calendar"

/**
 * @brief 所有联系人类数据的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_CONTACT "general.contact"

/**
 * @brief 所有数据库文件的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_DATABASE "general.database"

/**
 * @brief 所有消息类数据的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_MESSAGE "general.message"

/**
 * @brief 所有电子名片类数据的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_VCARD "general.vcard"

/**
 * @brief 所有导航类数据的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_NAVIGATION "general.navigation"

/**
 * @brief 导航定位类型，归属类型为NAVIGATION。
 *
 * @since 12
 */
#define UDMF_META_LOCATION "general.location"

/**
 * @brief 系统定义的卡片类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_FORM "openharmony.form"

/**
 * @brief 系统定义的桌面图标类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_APP_ITEM "openharmony.app-item"

/**
 * @brief 系统定义的像素图类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_PIXEL_MAP "openharmony.pixel-map"

/**
 * @brief 系统定义的原子化服务类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_ATOMIC_SERVICE "openharmony.atomic-service"

/**
 * @brief 系统定义的包（即目录的打包文件），归属类型为DIRECTORY。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_PACKAGE "openharmony.package"

/**
 * @brief 系统定义的能力包，归属类型为OPENHARMONY_PACKAGE。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HAP "openharmony.hap"

/**
 * @brief 同步多媒体集成语言类型，归属类型为XML文本类型。
 *
 * @since 12
 */
#define UDMF_META_SMIL "com.real.smil"

/**
 * @brief 标记语言文本类型，归属类型为PLAIN_TEXT。
 *
 * @since 12
 */
#define UDMF_META_MARKDOWN "general.markdown"

/**
 * @brief 传真图像的基本类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_FAX "general.fax"

/**
 * @brief J2 jConnect传真文件类型，归属类型为FAX。
 *
 * @since 12
 */
#define UDMF_META_JFX_FAX "com.j2.jfx-fax"

/**
 * @brief 电子传真文件类型，归属类型为FAX。
 *
 * @since 12
 */
#define UDMF_META_EFX_FAX "com.js.efx-fax"

/**
 * @brief X Window系统（X11）中使用的位图图像格式，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_XBITMAP_IMAGE "general.xbitmap-image"

/**
 * @brief 标签图形（TaggedGraphics）图像类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_TGA_IMAGE "com.truevision.tga-image"

/**
 * @brief 硅图（Silicon Graphics）图像类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_SGI_IMAGE "com.sgi.sgi-image"

/**
 * @brief 开放标准的高动态范围图像格式类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_OPENEXR_IMAGE "com.ilm.openexr-image"

/**
 * @brief FlashPix图像文件类型，归属类型为IMAGE。
 *
 * @since 12
 */
#define UDMF_META_FLASHPIX_IMAGE "com.kodak.flashpix.image"

/**
 * @brief 流媒体视频类型，归属类型为VIDEO。
 *
 * @since 12
 */
#define UDMF_META_REALMEDIA "com.real.realmedia"

/**
 * @brief Au数据格式，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_AU_AUDIO "general.au-audio"

/**
 * @brief 音频交换数据类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_AIFC_AUDIO "general.aifc-audio"

/**
 * @brief 单声道/立体声音频类型（Digidesign Sound Designer II），归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_SD2_AUDIO "com.digidesign.sd2-audio"

/**
 * @brief RealMedia音频类型，归属类型为AUDIO。
 *
 * @since 12
 */
#define UDMF_META_REALAUDIO "com.real.realaudio"

/**
 * @brief 开源XML基类型，归属类型为ARCHIVE。
 *
 * @since 12
 */
#define UDMF_META_OPENXML "org.openxmlformats.openxml"

/**
 * @brief 开源XML文档类型，归属类型为OPENXML和COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_WORDPROCESSINGML_DOCUMENT "org.openxmlformats.wordprocessingml.document"

/**
 * @brief 开源XML电子表格类型，归属类型为OPENXML和COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_SPREADSHEETML_SHEET "org.openxmlformats.spreadsheetml.sheet"

/**
 * @brief 开源XML演示文稿类型，归属类型为OPENXML和COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_PRESENTATIONML_PRESENTATION "org.openxmlformats.presentationml.presentation"

/**
 * @brief Office应用程序的开源文档类型，归属类型为ARCHIVE。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT "org.oasis.opendocument"

/**
 * @brief 开源文档类型，归属类型为OPENDOCUMENT和COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_TEXT "org.oasis.opendocument.text"

/**
 * @brief 开源文档电子表格类型，归属类型为OPENDOCUMENT和COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_SPREADSHEET "org.oasis.opendocument.spreadsheet"

/**
 * @brief 开源文档演示类型，归属类型为OPENDOCUMENT和COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_PRESENTATION "org.oasis.opendocument.presentation"

/**
 * @brief 开源文档图形类型，归属类型为OPENDOCUMENT和COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_GRAPHICS "org.oasis.opendocument.graphics"

/**
 * @brief 开源文档公式集类型，归属类型为OPENDOCUMENT。
 *
 * @since 12
 */
#define UDMF_META_OPENDOCUMENT_FORMULA "org.oasis.opendocument.formula"

/**
 * @brief Stuffit压缩格式类型（Stuffit archive），归属类型为ARCHIVE。
 *
 * @since 12
 */
#define UDMF_META_STUFFIT_ARCHIVE "com.allume.stuffit-archive"

/**
 * @brief VCalendar日历数据类型，归属类型为CALENDAR和TEXT。
 *
 * @since 12
 */
#define UDMF_META_VCS "general.vcs"

/**
 * @brief ICalendar日历数据类型，归属类型为CALENDAR和TEXT。
 *
 * @since 12
 */
#define UDMF_META_ICS "general.ics"

/**
 * @brief 所有可执行文件的基类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_EXECUTABLE "general.executable"

/**
 * @brief Microsoft Windows应用程序类型，归属类型为EXECUTABLE。
 *
 * @since 12
 */
#define UDMF_META_PORTABLE_EXECUTABLE "com.microsoft.portable-executable"

/**
 * @brief Java类文件类型，归属类型为EXECUTABLE。
 *
 * @since 12
 */
#define UDMF_META_SUN_JAVA_CLASS "com.sun.java-class"

/**
 * @brief 所有字体数据类型的基础类型，归属类型为OBJECT。
 *
 * @since 12
 */
#define UDMF_META_FONT "general.font"

/**
 * @brief TrueType字体类型，归属类型为FONT。
 *
 * @since 12
 */
#define UDMF_META_TRUETYPE_FONT "general.truetype-font"

/**
 * @brief TrueType collection字体类型，归属类型为FONT。
 *
 * @since 12
 */
#define UDMF_META_TRUETYPE_COLLECTION_FONT "general.truetype-collection-font"

/**
 * @brief OpenType字体类型，归属类型为FONT。
 *
 * @since 12
 */
#define UDMF_META_OPENTYPE_FONT "general.opentype-font"

/**
 * @brief PostScript字体类型，归属类型为FONT。
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_FONT "com.adobe.postscript-font"

/**
 * @brief PostScript Font Binary字体类型，归属类型为FONT。
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_PFB_FONT "com.adobe.postscript-pfb-font"

/**
 * @brief Adobe Type 1 字体类型，归属类型为FONT。
 *
 * @since 12
 */
#define UDMF_META_POSTSCRIPT_PFA_FONT "com.adobe.postscript-pfa-font"

/**
 * @brief 系统定义的备忘录数据类型，归属类型为COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HDOC "openharmony.hdoc"

/**
 * @brief 系统定义的笔记数据类型，归属类型为COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_HINOTE "openharmony.hinote"

/**
 * @brief 系统定义的样式字符串类型，归属类型为COMPOSITE_OBJECT。
 *
 * @since 12
 */
#define UDMF_META_OPENHARMONY_STYLED_STRING "openharmony.styled-string"

/**
 * @brief 系统定义的Want类型，归属类型为OBJECT。
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