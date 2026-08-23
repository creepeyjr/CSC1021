<h2>Stage 1</h2>
<p>Beginnings of my project, with the following commands functioning :</p>

<ul>
<li><strong>cd /path/to/somwhere</strong>     Changes the current working directory.</li>
<li><strong>clr  </strong>                    Wipes the screen of all text.</li>
<li><strong>dir </strong>                     List the contents of current directory.</li>
<li><strong>environ </strong>                 List all environment strings.</li>
<li><strong>echo Text of some sort.</strong>  Repeats back text typed after command. </li>
<li><strong>help </strong>                    Opens basic user manual.</li>
<li><strong>pause </strong>                   Halt all operations and inputs to shell until "Enter" is pressed.</li>
<li><strong>quit </strong>                    Close the shell.</li>
</ul>

<p>This Shell supports 2 modes, which can be controlled by how the shell is invoked.</p>

<ul>
    <li><strong>./simpleshell</strong> Will read individual command arguements typed into shell.</li>
    <li><strong>./simpleshell</strong> Will read individual command arguements typed into shell.</li>
</ul>

<h2>Stage 2</h2>

<p>A continuation from Stage 1, with the following advancements :</p>


<h4>External Command Execution</h4>
<p>Any command not recognised as a built-in is executed as an external program.

The shell will fork a child process and execute the program.
</p>

<h4>I/O Redirection</h4>
<p>The shell supports both strandard input and output redirection.</p>
<ul>
<li><strong>Output Redirection (Overwrite)</strong></li>
<p><strong>">"</strong> Redirects standard output to a file, overwriting the file if it exists.</p>

<li><strong>Output Redirection (Append)</strong></li>
<p><strong>">>"</strong>  Redirects standard output to a file, appending to the file if it exists.</p>

<li><strong>Input Redirection (Reading)</strong></li>
<p><strong> "&lt;" </strong>   Redirects standard input from a file.
</p>
</ul>

<h4>Background Execution</h4>
<p>The shell supports running programs in the background.</p>
<ul><li><strong>&</strong>   When a command ends with "&", the shell will return it's prompt immediately, while the program continues running.</li></ul>

<h2>Stage 3</h2>
<p>This was video documentation of the project, and there was no technical advancements required.</p>
