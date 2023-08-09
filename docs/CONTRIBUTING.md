# Contributing

We're really glad you're reading this, because we would love to have more developers contribute to this project! If you're passionate about making this project better, you're in the right place.

## Before contributing

If you encounter a bug or think of a useful feature, please [create a new issue](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/issues/new). Creating an issue before jumping into code ensures we can discuss it and determine whether it aligns with the direction of this project.

If you want to contribute to the project, regardless of whether it's a small bug fix or correcting a typo, please feel free to do so. Any help goes a long way! Also, contributions aren't necessarily all code related. Other contributions can be in the form of issues, pull requests, discussions, etc.

## Got a question or problem?

For quick questions there's no need to open an issue as you can reach us on [GitHub Discussions](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/discussions).

## Reporting a bug

Bugs are tracked as [GitHub issues](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/issues). Search open issues to see if someone else has reported a similar bug. If it's something new, [open an issue](https://github.com/makerdiary/nrf52840-mdk-usb-dongle/issues/new). We'll use the issue to have a conversation about the problem you want to fix.

When creating a new issue, please ensure the issue is clear and include additional details to help maintainers reproduce it:

* **Use a clear and descriptive title** for the issue to identify the problem.
* **Describe the exact steps which reproduce the problem** in as many details as possible.
* **Provide specific examples to demonstrate the steps.** Include links to files, or copy/pasteable snippets. If you're providing snippets in the issue, use Markdown code blocks.
* **Describe the behavior you observed** after following the steps and point out what exactly is the problem with that behavior.
* **Explain which behavior you expected to see** instead and why.
* **Include screenshots and animated GIFs** where possible.

## Sign-off your commits

A sign-off message in the following format is required on each commit in the pull request:

``` { .text .no-copy linenums="1" }
This is my commit message

Signed-off-by: First_Name Last_Name <My_Name@example.com>
```

The text can either be manually added to your commit body, or you can add either `-s` or `--signoff` to your usual git commit commands.

### Creating your signoff

Git has a `-s | --signoff` command-line option to append this automatically to your commit message:

``` bash linenums="1"
git commit --signoff --message 'This is my commit message'
```

or

``` bash linenums="1"
git commit -s -m "This is my commit message"
```

This will use your default git configuration which is found in `.git/config` and usually, it is the `username systemaddress` of the machine which you are using.

To change this, you can use the following commands (Note these only change the current repo settings, you will need to add `--global` for these commands to change the installation default).

Your name:

``` bash linenums="1"
git config user.name "First_Name Last_Name"
```

Your email:

``` bash linenums="1"
git config user.email "My_Name@example.com"
```

### How to amend a sign-off

If you have authored a commit that is missing the signed-off-by line, you can amend your commits and push them to GitHub

``` bash linenums="1"
git commit --amend --signoff
```

If you've pushed your changes to GitHub already you'll need to force push your branch after this with `git push -f`.
