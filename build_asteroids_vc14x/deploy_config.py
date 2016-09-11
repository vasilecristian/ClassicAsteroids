# -*- coding: utf-8 -*-
# Deployment settings for Asteroids.
# This file is autogenerated by the mkb system and used by the s3e deployment
# tool during the build process.

config = {}
cmdline = ['D:/tools/Marmalade/8.5/s3e/makefile_builder/mkb.py', 'd:/work/Asteroids/Asteroids.mkb', '--deploy-only', '--hub-data', 'D:/work/Asteroids/project_Asteroids/mkb-windows.txt', '--buildenv=VC14X']
mkb = 'd:/work/Asteroids/Asteroids.mkb'
mkf = ['d:\\tools\\marmalade\\8.5\\s3e\\s3e-default.mkf', 'd:\\tools\\marmalade\\8.5\\extensions\\s3eamazonads\\s3eamazonads.mkf', 'd:\\tools\\marmalade\\8.5\\modules\\iwutil\\iwutil.mkf', 'd:\\tools\\marmalade\\8.5\\modules\\third_party\\libjpeg\\libjpeg.mkf', 'd:\\tools\\marmalade\\8.5\\modules\\third_party\\libpng\\libpng.mkf', 'd:\\tools\\marmalade\\8.5\\modules\\third_party\\zlib\\zlib.mkf', 'd:\\tools\\marmalade\\8.5\\platform_libs\\android\\amazon-ads-android-sdk\\amazon-ads-android-sdk.mkf', 'd:\\tools\\marmalade\\8.5\\platform_libs\\iphone\\amazon-ads-ios-sdk\\amazon-ads-ios-sdk.mkf']

class DeployConfig(object):
    pass

######### ASSET GROUPS #############

assets = {}

assets['Default'] = [
    ('d:/work/Asteroids\data', '.', 0),
]

######### DEFAULT CONFIG #############

class DefaultConfig(DeployConfig):
    embed_icf = -1
    name = 'Asteroids'
    pub_sign_key = 0
    priv_sign_key = 0
    caption = 'Asteroids'
    long_caption = 'Asteroids'
    version = [0, 0, 1]
    config = ['d:/work/Asteroids\\data\\app.icf']
    data_dir = 'd:/work/Asteroids/data'
    mkb_dir = 'd:/work/Asteroids'
    iphone_link_lib = ['s3eAmazonAds']
    tvos_link_lib = []
    osx_ext_dll = []
    iphone_extra_string = []
    wp81_extra_pri = []
    ws8_ext_capabilities = []
    ws8_ext_native_only_dll = []
    win10_ext_uap_capabilities = []
    tizen_so = []
    tvos_extra_string = []
    tvos_link_libs = []
    win10_ext_native_dll = []
    ws81_ext_native_only_dll = []
    android_external_res = []
    win32_ext_dll = []
    tvos_link_libdirs = []
    wp8_ext_capabilities = []
    ws8_extra_res = []
    iphone_extra_plugins = []
    ws81_ext_managed_dll = []
    iphone_link_libdir = ['d:/tools/marmalade/8.5/extensions/s3eamazonads/lib/iphone']
    wp81_ext_capabilities = []
    android_extra_application_manifest = ['d:/tools/marmalade/8.5/extensions/s3eamazonads/source/android/ExtraAppManifests.xml']
    win10_extra_res = []
    ws8_ext_native_dll = []
    iphone_link_libdirs = []
    android_external_assets = []
    blackberry_extra_descriptor = []
    android_ext_target_sdk_version = [17]
    android_extra_manifest = []
    wp81_ext_sdk_ref = []
    tvos_link_libdir = []
    wp81_ext_device_capabilities = []
    android_extra_application_attributes_manifest = []
    win10_ext_capabilities = []
    linux_ext_lib = []
    android_ext_min_sdk_version = [4]
    wp81_ext_native_only_dll = []
    ws8_ext_managed_dll = []
    tvos_extra_plugins = []
    ws8_ext_sdk_manifest_part = []
    ws8_ext_device_capabilities = []
    ws81_extra_pri = []
    android_external_jars = ['d:/tools/marmalade/8.5/platform_libs/android/amazon-ads-android-sdk/third_party/lib/amazon-ads-5.5.149.jar', 'd:/tools/marmalade/8.5/extensions/s3eamazonads/lib/android/s3eAmazonAds.jar']
    win8_winrt_extra_res = []
    wp81_ext_sdk_manifest_part = []
    wp81_extra_res = []
    iphone_external_assets = []
    wp81_ext_managed_dll = []
    tvos_link_opts = []
    win10_ext_managed_dll = []
    iphone_extra_plist = ['d:/tools/marmalade/8.5/extensions/s3eamazonads/s3eAmazonAds.plist']
    ws81_ext_sdk_manifest_part = []
    ws81_ext_device_capabilities = []
    android_supports_gl_texture = []
    ws8_ext_sdk_ref = []
    tvos_asset_catalog = []
    osx_extra_plist = []
    wp8_ext_native_dll = []
    win10_ext_sdk_manifest_part = []
    tvos_extra_plist = []
    win10_extra_pri = []
    win10_ext_device_capabilities = []
    win8_phone_extra_res = []
    win8_store_extra_res = []
    win32_aux_dll = []
    iphone_link_opts = ['-Fd:/tools/marmalade/8.5/platform_libs/iphone/amazon-ads-ios-sdk/third_party/Ads -framework AmazonAd', '-weak_framework AdSupport -weak_framework CoreLocation -weak_framework SystemConfiguration', '-weak_framework CoreTelephony -weak_framework MediaPlayer', '-weak_framework EventKit -weak_framework EventKitUI']
    ws81_ext_sdk_ref = []
    wp8_extra_res = []
    ws81_ext_native_dll = []
    ws8_extra_pri = []
    wp8_ext_managed_dll = []
    android_extra_packages = []
    android_so = ['d:/tools/marmalade/8.5/extensions/s3eamazonads/lib/android/libs3eAmazonAds.so']
    wp8_ext_sdk_ref = []
    osx_extra_res = []
    ws81_extra_res = []
    wp81_ext_native_dll = []
    ws81_ext_capabilities = []
    iphone_link_libs = []
    android_extra_strings = []
    target = {
         'gcc_x86' : {
                   'debug'   : r'd:/work/Asteroids/build_asteroids_vc14x/Debug_Asteroids_VC14X_gcc_x86/Asteroids.so',
                   'release' : r'd:/work/Asteroids/build_asteroids_vc14x/Release_Asteroids_VC14X_gcc_x86/Asteroids.so',
                 },
         'gcc_x86_tizen' : {
                   'debug'   : r'd:/work/Asteroids/build_asteroids_vc14x/Debug_Asteroids_VC14X_gcc_x86_tizen/Asteroids.s86',
                   'release' : r'd:/work/Asteroids/build_asteroids_vc14x/Release_Asteroids_VC14X_gcc_x86_tizen/Asteroids.s86',
                 },
         'firefoxos' : {
                   'debug'   : r'd:/work/Asteroids/build_asteroids_vc14x/Debug_Asteroids_VC14X_firefoxos/Asteroids.js',
                   'release' : r'd:/work/Asteroids/build_asteroids_vc14x/Release_Asteroids_VC14X_firefoxos/Asteroids.js',
                 },
         'gcc_arm_android' : {
                   'debug'   : r'd:/work/Asteroids/build_asteroids_vc14x/Debug_Asteroids_VC14X_gcc_arm_android/Asteroids.so',
                   'release' : r'd:/work/Asteroids/build_asteroids_vc14x/Release_Asteroids_VC14X_gcc_arm_android/Asteroids.so',
                 },
         'arm_gcc' : {
                   'debug'   : r'd:/work/Asteroids/build_asteroids_vc14x/Debug_Asteroids_VC14X_gcc_arm/Asteroids.s3e',
                   'release' : r'd:/work/Asteroids/build_asteroids_vc14x/Release_Asteroids_VC14X_gcc_arm/Asteroids.s3e',
                 },
         'naclx86_64' : {
                   'debug'   : r'd:/work/Asteroids/build_asteroids_vc14x/Debug_Asteroids_VC14X_gcc_naclx86_64/Asteroids.so.s64',
                   'release' : r'd:/work/Asteroids/build_asteroids_vc14x/Release_Asteroids_VC14X_gcc_naclx86_64/Asteroids.so.s64',
                 },
         'aarch64_gcc' : {
                   'debug'   : r'd:/work/Asteroids/build_asteroids_vc14x/Debug_Asteroids_VC14X_gcc_aarch64/Asteroids.s3e',
                   'release' : r'd:/work/Asteroids/build_asteroids_vc14x/Release_Asteroids_VC14X_gcc_aarch64/Asteroids.s3e',
                 },
         'gcc_x86_android' : {
                   'debug'   : r'd:/work/Asteroids/build_asteroids_vc14x/Debug_Asteroids_VC14X_gcc_x86_android/Asteroids.so',
                   'release' : r'd:/work/Asteroids/build_asteroids_vc14x/Release_Asteroids_VC14X_gcc_x86_android/Asteroids.so',
                 },
         'x86' : {
                   'debug'   : r'd:/work/Asteroids/build_asteroids_vc14x/Debug_Asteroids_VC14X_x86/Asteroids.s86',
                   'release' : r'd:/work/Asteroids/build_asteroids_vc14x/Release_Asteroids_VC14X_x86/Asteroids.s86',
                 },
        }
    arm_arch = ''
    assets_original = assets
    assets = assets['Default']

default = DefaultConfig()
