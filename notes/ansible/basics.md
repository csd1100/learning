# Ansible
- Configuration as Code
- Idempotency is important in ansible.
- An operation is idempotent if the result of performing it once is exactly the same as the result of performing it repeatedly without any intervening actions.
- The task is idempotent if it's output remains same regardless.
e.g. If user is already present then task to add user shouldn't fail.

## Ansible config
- It is stored at location `/etc/ansible/ansible.cfg`
- e.g.
```
[defaults]
inventory = inventory
remote_user = ansible
host_key_checking = false

[privilege_escalation]
become = True
become_method = sudo
become_user = root
become_ask_pass = False
```
## Inventory
- Assets to be managed.
- Default inventory is in `/etc/ansible/hosts`.
- Can be defined per project in file format and using **`-i <filename>`** flag.

## Ad-hoc commands
- `ansible` command can be used to run ad-hoc commands
- ex. `ansible <host_name> -m <module_name> -a <args>`
- `ansible-doc` for checking documentation from cli. e.g. `ansible-doc -t module <module_name>`

## Playbooks
- Use `ansible-playbook` command
- Each playbook can have multiple plays.
- We can also use flags like `--start-at-task <taskname>` to run playbook from any stage or task.
- Each play has at least following properties: name, hosts, tasks.
- template of playbook:
```yaml
---
- name: play-name
  hosts: host1
  tasks:
    - name: task1
      <module_name>:
        key: value

- name: play-name2
  hosts: host2
  tasks:
    - name: task1
      debug:
        key: value
```

### Includes and Imports
- Includes are dynamic and used for conditionally including something.
- While, Imports are static and decided when ansible pre-processes the file.

### Best Practices
- Use variables to separate site-specific playbooks.
- Make your playbook such that it will be mostly common for all the sites.
- But for specific sites it should be dynamic using variables.
- Use facts for site-specific work if needed.
- Decouple site-specific and generic tasks.
- Use list for installing packages instead of single package per task.
- Security:
    - do not do password-less ssh keys
    - do not set `become = true` at top level
    - use `-b -K` if necessary but not convenient
    - use ssh key with password and use ssh-agent for convenience and use ssh-add to add key
    - do not use NOPASSWD /etc/sudoers, use timestamp to increase timeout of sudo

### Variables
- Variables can be user-defined or ansible gathered facts.
- They are declared using `vars` key in the play.
The variables that are defined in one play using `vars` can't be used in another.
```yaml
---
- name: play-name
  hosts: host1
  vars:
    name: value
  tasks:
    - name: task1
      module_name:
        key: value
```
- If we use `ansible-playbook -e <name>=<value>` flag the value will be overridden.
- We can define variables in files and include `var_files:`.
- We can also prompt for value using `vars_prompt:`.
- Variables can also be defined dynamically for task using `set_fact` module. Which sets variable only for **specific** host.
- We can create a `group_vars` directory, in which we can define vars for group of hosts defined in inventory.
The name of the files of vars should be same as group name.
- Use `{{ var_name }}` to access variables. If value starts with variables use `"{{ myvar }} is set"`.
- In `when` `{{ }}` are not required.
- Value with variables should be in `""`
- It is not good practise to define variables in playbook as it makes harder to decouple site-specific information.

### Ansible facts.
- Facts are variables generated by ansible in fact gathering stage that contain information about site(device).
- They contain information about host. And they are stored in `ansible_facts` variable which is dictionary.
- For version older than 2.5 they generally start with `ansible_`.
- They can be accessed as `ansible_facts['default_ipv4']['address']` which is preferred way.
- Otherwise as `ansible_facts.default_ipv4.address` not preferred.
- Or in older versions as ansible_default_ipv4.address
- Gathering facts takes time and if you do not need to use facts then for a play it can be disabled in play header using `gather_facts: no`.
- `setup` module gives you all the facts if you want to see them before hand.
- If facts gathering is slow setup host name resolution i.e. specify entries in `/etc/hosts` for faster resolution.

### Magic variables
- Magic variables are variables that reserved ansible variables and cannot be used.
- they are
    - hostvars
    - groups
    - group_names
    - inventory_hostname
    - inventory_hostname_short

### Registers
- They are variables to store command result
- We can use `register: <var_name>` to store result of command.
- e.g.
```yaml
---
- name: Registers
  hosts: localhost
  tasks:
    - name: ls
      shell: ls
      register: ls_out
    - debug:
        var: ls_out
    - debug:
        msg: status code of ls {{ ls_out['rc'] }}
```

### Conditionals
#### Handlers
- A handler is task is only executed when task it is triggered by has changed something.
- They are executed after tasks in playbooks.
- If any task fails after task that triggers handler then handler is not executed but `force_handlers` a boolean value can be used in play definition to run handler forcefully.
- Handlers are defined using `handlers:` in play.
- `notify:` is used in tasks to trigger handlers.
e.g.

```yaml
---
- name: handlers play
  hosts: localhost
  tasks:
    - name: write hello_world
      shell: echo hello_world > /tmp/tmp
      notify:
        - copy_hello_world
  handlers:
    - name: copy_hello_world
      shell: cp /tmp/tmp /tmp/hello_world

```

#### When
- Tasks are run only when a condition is true.
- Using `when:` in task definition.
- We can use `when: myvar is defined` to check if variable is present.
- We can use `when: myvar in vars` to check if value of `myvar` is present in `vars` variable.
- We can also use python functions in when like `find()`
- We do not need to use `{{}}` to access variable.

#### Blocks
- `block` is defined in tasks.
- It is group of tasks. We can use it to combine tasks with common `when`.
- Can be used for error handling. `rescue` can be used when the task in `block` fails.
- `always` will run regardless of `block` fails or succeeds.
- It is kind of like try/catch/finally.
- We cannot use items/loops in `block`s.
- e.g.

```yaml
---
- name: Blocks
  hosts: localhost
  tasks:
    - name: blocks example
      block:
        - name: task that can fail
          command:
            cmd: /usr/bin/rm /tmp/somefile
      rescue:
        - name: run when above fails
          command:
            cmd: /usr/bin/touch /tmp/anyfile
      always:
        - name: always run
          debug:
            msg: /usr/bin/logger hello
```
### Loops
- Can be done using `loop:` in the past using `with_<X>:`.
- Each item in the loop can be accessed using `item`.
- `with_items:` is equivalent to `loop`.
- `with_files` has `item` which is a file.
- filters can be used instead of `with_<X>`
- e.g.
```yaml
---
- name: loops example
  hosts:
  vars:
    myvar:
      - crond
      - sshd
  tasks:
    - name: loop through services and start them
      service:
        name: "{{ item }}"
        state: started
      loop: "{{ myvar }}"
```

### Failure Handling
- `ignore_errors:` can be used to ignore failed tasks. It can be defined at task or play level.
- `force_handlers:` can also be used to run handler even when other tasks do fail.
- `fail` module can be used to inform why a task has failed
- `failed_when:` can be used to define a failure condition.
- To use `fail` module and `failed_when` the result of task should be registered.
- And `ignore_errors:` should be true/yes so we can handle failure accordingly.
- In below example "see if get here" will run because we are using `ignore_errors`
```yaml
---
- name: failed_when example
  hosts: localhost
  tasks:
    - name: run something
      command: echo hello world
      ignore_errors: yes
      register: command_result
      failed_when: "'world' in command_result['stdout']"
    - name: see if get here
      debug:
        msg: test
    - name: print error
      fail:
        msg: task failed
```

### Tags
- Tags can be specified using `tags:`
- `--list-tags` will list all tags.
- `-t <tags_names>` will run tasks or plays with only that tasks.
- `--skip-tags <tags_names>` will run all tasks without the tags specified.

### Delegation
- We can use `delegate_to:` to change task to run on specific host.
- Requirements for delegation to work on specified host:
    - host must have python installed
    - SSH access to managed hosts is enabled
    - Hostname to ip address resolution working (either using dns or /etc/hosts)
    - host must exist in inventory
- e.g.
    - It can be used to verify something from `localhost` by adding task to verify and delegate that to `localhost`.
    - Copy/Sync files between managed hosts.

### Ansible collections
- New way to bundle ansible contents
- Collections may contains:
    - modules
    - rules
    - plugins
- Collection have FQCN (Fully Qualified Collection Name) e.g. `ansible.builtin.copy`.
- The FQCN can also be defined in play header to make them backwards compatible.
- Collections can be defined at play level using `collections:` array.
- In ansible version 2.9 the collections need to be installed before hand.
We can specify required collections in `requirements.yml`.

### Ansible roles
- Community provided standard solution for common tasks like setting up docker.
- They are on ansible galaxy.
- We can also create roles yourself.
- Tasks in roles are executed before tasks.
- We can change that behavior with `pre_tasks:` flag.
- We need to install a role using command `ansible-galaxy role install <role_name>`
- To create a role:
    - Use `ansible-galaxy roles init <role_name>`
    - This command creates required directory structure.

## Ansible vault
- Store secure data using encryption.
- Can be used using `ansible-vault` command

# Ansible Galaxy
- `ansible-galaxy` command can be used to manage roles and collection from [Ansible Galaxy](https://galaxy.ansible.com).