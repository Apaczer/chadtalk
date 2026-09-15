import glob
import json
import os
import re
import sys
from datetime import datetime


def convert_transcripts(output_dir="conversations", log_file=None):
    os.makedirs(output_dir, exist_ok=True)

    if log_file:
        log_files = [log_file]
    else:
        pattern = os.path.expanduser(
            "~/.gemini/antigravity-cli/brain/*/.system_generated/logs/transcript.jsonl"
        )
        log_files = glob.glob(pattern)

        if not log_files:
            print("Error: No transcript logs found.", file=sys.stderr)
            sys.exit(1)

    for log_file in sorted(log_files, key=os.path.getmtime):
        print(f"Reading transcript from: {log_file}")

        timestamp = os.path.getmtime(log_file)
        output_file = os.path.join(
            output_dir,
            f"transcript_{datetime.fromtimestamp(timestamp):%Y%m%d_%H%M%S}.md",
        )

        with open(log_file, "r", encoding="utf-8") as f, \
             open(output_file, "w", encoding="utf-8") as out:

            for line in f:
                line = line.strip()

                if not line:
                    continue

                try:
                    msg = json.loads(line)
                except json.JSONDecodeError:
                    continue

                msg_type = msg.get("type")

                if msg_type == "USER_INPUT":
                    content = msg.get("content", "")

                    m = re.search(
                        r"<USER_REQUEST>(.*?)</USER_REQUEST>",
                        content,
                        re.DOTALL,
                    )

                    user_text = m.group(1).strip() if m else content.strip()

                    if user_text:
                        out.write(
                            f"\n## 👤 User\n\n"
                            f"{user_text}\n\n"
                            f"---\n"
                        )

                elif msg_type == "PLANNER_RESPONSE" and msg.get("content"):
                    bot_text = msg.get("content", "").strip()

                    out.write(
                        f"\n## 🤖 Assistant\n\n"
                        f"{bot_text}\n\n"
                        f"---\n"
                    )

        print(f"Exported: {output_file}")


if __name__ == "__main__":
    output_dir = sys.argv[1] if len(sys.argv) > 1 else "conversations"
    convert_transcripts(output_dir=output_dir)
