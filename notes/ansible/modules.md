# Ansible modules
\* - Always prefer specific module over this to do something.

- `ansible.builtin.command`<sup>*</sup>
    - Useful to run commands on hosts without shell and piping outputs doesn't work.

- `ansible.builtin.shell`<sup>*</sup>
    - Useful to run command using shell, piping works.

- `ansible.builtin.raw`<sup>*</sup>
    - Useful to run commands without python installed.
    - All modules use python so if python is not installed then use this to run command.

- `ansible.builtin.package`<sup>*</sup>
    - Useful to install packages on all distros.
    - But it's always better to use specific module than generic.

- `ansible.builtin.assert`
    - Can be used to assert conditions.
    - We can use it to display failure and success message.
    - e.g.
    ```yaml
    ---
    - name: assert
      hosts: localhost
      vars_prompt:
      - name: filesize
        prompt: "specify filesize"
        private: no
      tasks:
        - name: assert something
          assert:
            that:
            # convert filesize to int
            - {{ ( filesize | int ) <= 100 }}
            - {{ ( filesize | int ) >= 1 }}
            fail_msg: "file size must be between 1 - 100"
            success_msg: "file size is good creating a file"
        - name: "create the file of size {{ filesize }}"
          command: dd if=/dev/zero of=/bigfile bs=1 count={{ filesize }}
    ```

- `ansible.builtin.copy`
    - Copy from controlled host to managed hosts.
    - Can be also used to copy content from file.
    - e.g.
    ```yaml
    # just the task
    - name: Copy file
      ansible.builtin.copy:
        # on control host
        src: /etc/hosts
        # on managed host
        dest: /tmp/
    ```

- `ansible.posix.synchronize`
    - Requires `rsync` to be installed.
    - Efficient than `ansible.builtin.copy` for copying large number of files.

- `ansible.builtin.fetch`
    - Copy from managed host to controlled host.
    - By default store files in `<hostname>/path/to/file` path.
    ```yaml
    - name: fetch file
      ansible.builtin.fetch:
        # on managed host
        src: /tmp/hosts
        # on controll host at path /tmp/<hostname>/tmp/hosts
        dest: /tmp/
    ```

- `ansible.builtin.replace`
    - Can be used to replace text using regex.

- `ansible.builtin.lineinfile`
    - Add single line to file.

- `ansible.builtin.blockinfile`
    - Add multiple line to file.
    - e.g.
    ```yaml
    - name: add lines to file
      ansible.builtin.blockinfile:
        path: /tmp/hosts
        # using | for layout
        block: |
            192.168.74.123 host.example.com
        state: present
    ```

- `ansible.builtin.stat`
    - Information about a file.
    - e.g.
    ```yaml
    - name: get MD5 sum of file
      ansible.builtin.stat:
        path: /tmp/hosts
        checksum_algorithm: md5
        register: result
    - name: print MD5 sum of file
      ansible.builtin.debug:
        var: result.stat.checksum
    ```
- `ansible.builtin.find`
    - Find files and similar to linux find.
    - e.g.
    ```yaml
    - name: find ansible.cfg files
      find:
        paths: /home/ansible/rhce8-live
        patterns: 'ansible.cfg'
        recurse: yes
      register: output
    - debug:
        var: item.path
      with_items: "{{ output.files }}"
    - blockinfile:
        path: "{{ item.path }}"
        insertafter: "defaults"
        marker: "##<!-- {mark} ANSIBLE MANAGED BLOCK -->##"
        block: |
          fact_caching = redis
          fact_caching_timeout = 3600
          fact_caching_connection = localhost:6379:0
      with_items: "{{ output.files }}"
    ```
- `ansible.builtin.template`
    - Ansible uses jinja2 template files
    - The templates used by playbooks are stored in `templates` directory.
    - template: location - `./templates/template.j2`
    ```jinja2
    Running on {{ ansible_facts['distribution'] }}
    ```
    - playbook:
    ```yaml
    - name: install motd
      template:
        src: template.j2
        dest: /etc/motd
        owner: root
        group: root
        mode: 0644
    ```
