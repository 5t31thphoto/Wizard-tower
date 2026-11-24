#!/usr/bin/env python3
"""Merge a PlatformIO ESP32 build into a single flash-at-zero image."""
from pathlib import Path
import argparse
import subprocess
import sys

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--env", default="m5stack-core2")
    ap.add_argument("--output", default="website/firmware/wizards-keep-merged.bin")
    ap.add_argument("--flash-size", default="16MB")
    args = ap.parse_args()
    root = Path(__file__).resolve().parents[1]
    build = root / ".pio" / "build" / args.env
    boot = build / "bootloader.bin"
    part = build / "partitions.bin"
    app = build / "firmware.bin"
    boot_app = Path.home() / ".platformio" / "packages" / "framework-arduinoespressif32" / "tools" / "partitions" / "boot_app0.bin"
    if not boot_app.exists():
        candidates = list((Path.home()/".platformio/packages").glob("framework-arduinoespressif32*/tools/partitions/boot_app0.bin"))
        if candidates: boot_app = candidates[0]
    missing = [str(p) for p in (boot, part, app, boot_app) if not p.exists()]
    if missing:
        print("Missing build inputs:\n" + "\n".join(missing), file=sys.stderr)
        return 2
    out = root / args.output
    out.parent.mkdir(parents=True, exist_ok=True)
    cmd = [sys.executable, "-m", "esptool", "--chip", "esp32", "merge_bin",
           "-o", str(out), "--flash_mode", "qio", "--flash_freq", "80m",
           "--flash_size", args.flash_size,
           "0x1000", str(boot), "0x8000", str(part),
           "0xe000", str(boot_app), "0x10000", str(app)]
    subprocess.run(cmd, check=True)
    print(f"Merged firmware: {out} ({out.stat().st_size} bytes)")
    return 0
if __name__ == "__main__":
    raise SystemExit(main())
