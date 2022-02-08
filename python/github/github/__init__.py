__version__ = '0.1.0'

from github import Github

g = Github("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")

for asset in g.get_repo('kewazo/neoflash').get_latest_release().get_assets():
    print(asset.url)
