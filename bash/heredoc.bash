#!/usr/bin/env bash

set -euo pipefail
# shellcheck disable=SC2034
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

var="1"

cat >&1 <<EOF
${var}
\${var}
EOF

cat >&1 <<EOF
SECRET="$(python3 -c 'import secrets; print(secrets.token_urlsafe(16))')"
EOF
