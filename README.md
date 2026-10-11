# XH Multiscreen · Form Monitor C6

一块放在桌面的 ESP32-C6 小屏：通过 Formlabs Dashboard API 监看打印机，同时显示翻页时钟与天气。

**开发中：`2.0.0-formlabs-alpha.9`。** 当前公开的是 Form Monitor C6 专用固件与必要的共享 C6 源码，不是 macOS 多屏灵犀应用，也不是通用 C6 固件的完整发布。它是 XH_Lab 的独立创作项目，非 Formlabs 官方产品。

## 硬件与功能

- Waveshare **ESP32-C6-LCD-1.3**，ST7789V2，240 × 240 LCD，4 MB Flash。其他芯片、板型和容量不在支持范围内。
- 最多配置三台 Formlabs 打印机；独立任务、凭据与缓存，支持任务状态、进度、剩余时间、材料、层数和可用的任务图片。需要用户自行获取 Dashboard API 的访问权限及凭据。
- 翻页时钟、可关闭的天气卡片、双语界面、像素或平滑数字、四档旋转、亮度、自动轮转与可选的背光休眠。
- 两台以上打印机自动加入总览；单台卡片可选标准、超大百分比或剩余时间样式。
- 本地网页配网、设置与设备实际 RGB565 帧预览；虚拟打印机演示会明确标为 DEMO，不冒充真实打印状态。
- BOOT 单击翻页、双击详情/确认、长按约 1.5 秒进入设置/返回。RST 是硬件重启键。

## 构建

需要 Node.js、PlatformIO Core 和 Git。建议 Python 3.11 或更高版本；安装 PlatformIO 后确保 `pio` 可用。

```sh
git clone https://github.com/XHFO/XH-Multiscreen.git
cd XH-Multiscreen
node scripts/embed-formlabs-c6-portal.mjs
pio run -d Tools/FormlabsC6Firmware -e formlabs-c6
```

PlatformIO 会根据 [platformio.ini](Tools/FormlabsC6Firmware/platformio.ini) 拉取固定版本的 Espressif 平台及 ESP-IDF 依赖。输出在 `Tools/FormlabsC6Firmware/.pio/build/formlabs-c6/`。仓库只发布源码，不包含预编译固件、设备备份或用户配置。

## 开发测试

网页和运行时逻辑测试可以单独运行：

```sh
node scripts/embed-formlabs-c6-portal.mjs --check
node Tools/FormlabsC6Firmware/tests/portal_test.mjs
node Tools/FormlabsC6Firmware/tests/autosave_test.mjs
node Tools/FormlabsC6Firmware/tests/preview_test.mjs
node Tools/FormlabsC6Firmware/tests/display_runtime_test.mjs
node Tools/FormlabsC6Firmware/tests/overview_runtime_test.mjs
```

macOS 下的完整专用测试还需要 Xcode Command Line Tools（Clang / Apple SDK / CoreGraphics）及 ESP-IDF 的 cJSON 源码。安装构建依赖后运行：

```sh
bash scripts/test-formlabs-c6.sh
```

默认读取 `~/.platformio/packages/framework-espidf/components/json/cJSON`。若安装在其他位置，可通过 `LINGXI_CJSON_ROOT` 指定 cJSON 源码目录。生成的预览图属于测试样例，不是真实打印机或 LCD 照片。

## 安装前必读

这是开发固件，**不自动连接或刷写设备**。先确认板型、芯片、Flash 容量、分区表，并保存可恢复的完整私密备份。不要把备份或真实凭据提交到仓库。

- 仅当现有分区表完全相同，才可按既有程序分区更新：`ota_data_initial.bin` → `0x10000`，`firmware.bin` → `0x20000`。需要核对每个文件、目标地址和写入回读。
- 新板或不同分区布局不能套用保留配置的更新方式。首次安装需按构建输出中的烧录参数单独评估 bootloader 与分区表，不提供通用自动烧录命令。
- 不以整片擦除或合并镜像覆盖来声称保留配置。项目配置命名空间为 `form_monitor` / `form_weather`；通用 C6 的配置不会自动导入。
- OTA 接口保留，但曾出现实机写入校验拒绝，**尚未验证为可靠升级路径**。不要把 API 存在当作 OTA 已可用。

## 配网与隐私

首次连接设备的 `Formlabs-C6-xxxxxx` 2.4 GHz 热点，打开 `http://192.168.4.1/`。联网后查看设备屏幕或路由器分配的实际 IP，再访问 `http://设备IP/standalone`。不保证 `.local` 可解析。

天气默认关闭，位置和打印机凭据默认空。启用天气会将用户配置的经纬度发送给 Open-Meteo；Formlabs 凭据用于其授权服务。网页不回显 Secret，不使用浏览器持久化存储，但设备 Flash 会保存配置；本地 HTTP 与 Flash **不提供加密传输或加密存储保证**。仅在可信局域网使用，不将设备端口暴露至公网。

## 验证边界与参与

自动测试覆盖配置迁移、保存冲突、打印机身份/缓存隔离、页面行为及渲染。源码已独立构建与测试；这些检查不证明真实三台打印机联网、长期稳定性、API 服务可用性、LCD 物理色彩/可读性或动画观感。欢迎通过 Issues 提交脱敏反馈或 Pull Requests；不要附 Wi-Fi 密码、API Secret、完整 Flash dump、真实设备序列号或未脱敏日志。

更多实现与历史版本说明见 [专用固件文档](Tools/FormlabsC6Firmware/README.md)。

## 许可

项目代码采用 [MIT](LICENSE)。第三方字体、QR 实现及外部工具链保留各自许可，见 [THIRD_PARTY.md](THIRD_PARTY.md)。本仓库不包含网站专题、实拍照片、外壳图纸或模型；模型不受本仓库 MIT 许可覆盖。
