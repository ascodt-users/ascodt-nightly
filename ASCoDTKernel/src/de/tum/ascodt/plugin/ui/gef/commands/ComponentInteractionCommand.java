package de.tum.ascodt.plugin.ui.gef.commands;


import org.eclipse.gef.commands.Command;

import de.tum.ascodt.plugin.ui.gef.model.Component;


public class ComponentInteractionCommand extends Command {
  protected Component source;
  protected int mode;

  /**
   * @return whether we can apply changes
   */
  @Override
  public boolean canExecute() {
    return source != null && mode > 0 && mode < 3;
  }

  public void setMode(int mode) {
    this.mode = mode;
  }

  public void setSource(Component source) {
    this.source = source;
  }
}
