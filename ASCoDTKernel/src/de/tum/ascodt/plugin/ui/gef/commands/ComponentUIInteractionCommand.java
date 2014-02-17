package de.tum.ascodt.plugin.ui.gef.commands;


public class ComponentUIInteractionCommand extends ComponentInteractionCommand {
  @Override
  public void execute() {
    source.setUIEnable(mode == 1);
  }
}
