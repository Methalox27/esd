import subprocess
import sys

# ==========================================
# GCS RECEIVER CONFIGURATION
# ==========================================
PORT = "5000"

def start_receiver():
    print("=======================================")
    print("🚁 DRONE GROUND CONTROL STATION")
    print("=======================================")
    print(f"📡 Listening for raw video packets on UDP port {PORT}...")
    print("⚡ Zero-latency mode enabled (sync=false).")
    print("Press Ctrl+C to close the video feed.")
    print("=======================================\n")

    # Bypassing the Windows PATH limit by pointing directly to the .exe
    gst_path = r"C:\Program Files\gstreamer\1.0\msvc_x86_64\bin\gst-launch-1.0.exe"

    # The GStreamer pipeline to catch and instantly display the video
    pipeline = (
        f'"{gst_path}" -v udpsrc port={PORT} ! '
        f"tsdemux ! h264parse ! avdec_h264 ! "
        f"autovideosink sync=false"
    )

    try:
        # Run the GStreamer receiver
        subprocess.run(pipeline, shell=True, check=True)
        
    except KeyboardInterrupt:
        print("\n🛑 Video feed closed by user.")
        sys.exit(0)
    except subprocess.CalledProcessError as e:
        print(f"\n❌ Error: The GStreamer pipeline crashed. Details: {e}")
        sys.exit(1)
    except FileNotFoundError:
        print(f"\n❌ Error: Could not find GStreamer at {gst_path}")
        sys.exit(1)

if __name__ == "__main__":
    start_receiver()
