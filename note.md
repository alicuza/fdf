# Makefile

- handling different release types, like having a `make debug` command, needs some additional work, like having .dotfiles that track which release type currently exists and handle it without relinking unnecessarily.
- Felix had the idea of using an environment variable instead of the .dotfiles. But how would an env var retain information from the last compilation to know whether it needs to fclean first or not.

# fdf
## Inspiration
[https://github.com/ailopez-o/42Barcelona-FdF](this mofo projects to a globe)

# tmux
## Options

This is how to find out what options are currently set, by default and by the currently active config file:
```
tmux show -g
tmux show -gw    # window options
tmux show -gp    # pane options
```

