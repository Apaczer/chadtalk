#!/usr/bin/env python3
import glob
import json
import os
import re
import sys

def convert_transcript(output_file="CONVERSATION.md", log_file=None):
    if not log_file:
        pattern = os.path.expanduser("~/.gemini/antigravity-cli/brain/*/.system_generated/logs/transcript_full.jsonl")
        log_files = glob.glob(pattern)
        if not log_files:
            print("Error: No transcript logs found.", file=sys.stderr)
            sys.exit(1)
        log_file = max(log_files, key=os.path.getmtime)

    print(f"Reading transcript from: {log_file}")

    with open(log_file, "r", encoding="utf-8") as f, open(output_file, "w", encoding="utf-8") as out:
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
                m = re.search(r"<USER_REQUEST>(.*?)</USER_REQUEST>", content, re.DOTALL)
                user_text = m.group(1).strip() if m else content.strip()
                out.write(f"\n## 👤 User\n\n{user_text}\n\n---\n")
            elif msg_type == "PLANNER_RESPONSE" and msg.get("content"):
                bot_text = msg.get("content", "").strip()
                out.write(f"\n## 🤖 Assistant\n\n{bot_text}\n\n---\n")

    print(f"Successfully exported conversation to: {output_file}")

if __name__ == "__main__":
    out_name = sys.argv[1] if len(sys.argv) > 1 else "CONVERSATION.md"
    convert_transcript(output_file=out_name)
