package de.tum.ascodt.plugin.ui.gef.commands;


import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.RequestConstants;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.requests.ChangeBoundsRequest;

import de.tum.ascodt.plugin.ui.gef.model.StickyNote;


public class StickyNoteSetConstraintCommand extends Command {
  /** Stores the new size and location. */
  private final Rectangle newBounds;
  /** Stores the old size and location. */
  private Rectangle oldBounds;
  /** A request to move/resize an edit part. */
  private final ChangeBoundsRequest request;

  /** Shape to manipulate. */
  private final StickyNote note;

  /**
   * Create a command that can resize and/or move a note.
   * 
   * @param note
   *          the note to manipulate
   * @param req
   *          the move and resize request
   * @param newBounds
   *          the new size and location
   * @throws IllegalArgumentException
   *           if any of the parameters is null
   */
  public StickyNoteSetConstraintCommand(StickyNote note,
                                        ChangeBoundsRequest req,
                                        Rectangle newBounds) {
    if (note == null || req == null || newBounds == null) {
      throw new IllegalArgumentException();
    }
    this.note = note;
    request = req;
    this.newBounds = newBounds.getCopy();
    setLabel("move / resize");
  }

  /*
   * (non-Javadoc)
   * 
   * @see org.eclipse.gef.commands.Command#canExecute()
   */
  @Override
  public boolean canExecute() {
    Object type = request.getType();
    // make sure the Request is of a type we support:
    return RequestConstants.REQ_MOVE.equals(type) || RequestConstants.REQ_MOVE_CHILDREN.equals(type) ||
           RequestConstants.REQ_RESIZE.equals(type) ||
           RequestConstants.REQ_RESIZE_CHILDREN.equals(type);
  }

  /*
   * (non-Javadoc)
   * 
   * @see org.eclipse.gef.commands.Command#execute()
   */
  @Override
  public void execute() {
    oldBounds = new Rectangle(note.getLocation(), note.getSize());
    redo();
  }

  /*
   * (non-Javadoc)
   * 
   * @see org.eclipse.gef.commands.Command#redo()
   */
  @Override
  public void redo() {
    note.setSize(newBounds.getSize());
    note.setLocation(newBounds.getLocation());
  }

  /*
   * (non-Javadoc)
   * 
   * @see org.eclipse.gef.commands.Command#undo()
   */
  @Override
  public void undo() {
    note.setSize(oldBounds.getSize());
    note.setLocation(oldBounds.getLocation());
  }
}
